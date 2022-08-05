/*
 * Copyright (c) 2022 Trail of Bits, Inc.
 */

#pragma once

#include "Compiler.h"
#include "Diagnostic.h"
#include "Job.h"

#include <fcntl.h>
#include <unistd.h>

#include <cassert>
#include <sstream>
#include <iostream>
#include <unordered_set>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbitfield-enum-conversion"
#pragma GCC diagnostic ignored "-Wimplicit-int-conversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wshorten-64-to-32"
#include <clang/Lex/PPCallbacks.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/PreprocessorOptions.h>
#pragma GCC diagnostic pop

#include "../AST/AST.h"
#include "../AST/Token.h"
#include "../Util/FileManager.h"

namespace pasta {

// Tracks open files.
class ParsedFileTracker : public clang::PPCallbacks {
 private:
  clang::SourceManager &sm;
  const clang::LangOptions &lang_opts;
  const pasta::FileManager fm;
  std::shared_ptr<pasta::FileSystem> fs;
  const std::filesystem::path cwd;

  ASTImpl * const ast;

  // Tracks whether or not we've tokenized a file.
  std::unordered_set<pasta::FileImpl *> seen;
 public:

  explicit ParsedFileTracker(clang::SourceManager &sm_,
                             const clang::LangOptions &lang_opts_,
                             const pasta::FileManager &fm_,
                             std::filesystem::path cwd_,
                             ASTImpl *ast_)
      : sm(sm_),
        lang_opts(lang_opts_),
        fm(fm_),
        fs(fm.FileSystem()),
        cwd(std::move(cwd_)),
        ast(ast_) {}

  virtual ~ParsedFileTracker(void) {}

  void Clear(void) {
    seen.clear();
    fs.reset();
  }

  // Each time we enter a source file, try to keep track of it.
  void FileChanged(clang::SourceLocation loc,
                   clang::PPCallbacks::FileChangeReason reason,
                   clang::SrcMgr::CharacteristicKind file_type,
                   clang::FileID file_id = clang::FileID()) final {

    if (clang::PPCallbacks::EnterFile == reason ||
        clang::PPCallbacks::ExitFile == reason) {
      switch (file_type) {
        case clang::SrcMgr::CharacteristicKind::C_User:
        case clang::SrcMgr::CharacteristicKind::C_System:
        case clang::SrcMgr::CharacteristicKind::C_ExternCSystem:
          break;
        case clang::SrcMgr::CharacteristicKind::C_User_ModuleMap:
        case clang::SrcMgr::CharacteristicKind::C_System_ModuleMap:
          return;
      }
    } else {
      return;
    }

    if (clang::PPCallbacks::EnterFile == reason) {
      assert(loc.isValid());
      assert(loc.isFileID());
      file_id = sm.getFileID(loc);
    }

    const clang::FileEntry *fe = sm.getFileEntryForID(file_id);
    if (!fe) {
      return;
    }

    std::filesystem::path fs_path = fs->ParsePath(
        fe->getName().str(), cwd, fs->PathKind());
    Result<Stat, std::error_code> fs_stat = fs->Stat(fs_path, cwd);
    if (!fs_stat.Succeeded()) {
      assert(false);
      return;
    }

    Result<File, std::error_code> maybe_file = fm.OpenFile(fs_stat.TakeValue());
    if (!maybe_file.Succeeded()) {
      assert(false);
      return;
    }

    File file = maybe_file.TakeValue();

    // Keep a mapping of Clang file IDs to parsed files.
    auto old_file_it = ast->id_to_file.find(file_id.getHashValue());
    if (old_file_it == ast->id_to_file.end()) {
      ast->id_to_file.emplace(file_id.getHashValue(), file);
    } else {
      assert(old_file_it->second.impl.get() == file.impl.get());
    }

    // If we've seen this file already, then don't tokenize it.
    if (auto [seen_it, added] = seen.emplace(file.impl.get()); !added) {
      return;
    }

    auto maybe_data = file.Data();
    if (!maybe_data.Succeeded()) {
      return;
    }

    ast->parsed_files.emplace_back(std::move(file));

    std::unique_lock<std::mutex> locker(file.impl->tokens_lock);
    if (file.impl->has_tokens) {
      return;
    }

    auto data = maybe_data.TakeValue();
    file.impl->has_tokens = true;
    if (data.empty()) {
      return;
    }

    const char * const buff_begin = &(data.front());
    const char * const buff_end = &(data[data.size()]);
    clang::Lexer lexer(loc, lang_opts, buff_begin, buff_begin, buff_end);
    lexer.SetKeepWhitespaceMode(true);  // Implies keep comments.

    // Raw lex this file's tokens.
    clang::Token tok;
    while (!lexer.LexFromRawLexer(tok)) {
      assert(!tok.hasLeadingEmptyMacro());
      assert(!tok.isAnnotation());
      if (tok.is(clang::tok::eof)) {
        break;
      }
      const auto tok_loc = tok.getLocation();
      auto offset = sm.getFileOffset(tok_loc);
      assert(offset < data.size());
      assert((offset + tok.getLength()) <= data.size());
      auto tok_kind = tok.getKind();

      uint16_t is_pp_keyword = 0;
      uint16_t is_objc_keyword = 0;
      uint16_t alt_keyword = 0;

      if (clang::tok::isAnyIdentifier(tok_kind)) {
        assert(tok_kind == clang::tok::raw_identifier);
        tok_kind = clang::tok::identifier;

        // Try to form a `pp_*` keyword, or an `objc_*` keyword.
        if (!file.impl->tokens.empty()) {
          const auto ident = tok.getRawIdentifier();
          const auto num_file_toks = static_cast<uint32_t>(
              file.impl->tokens.size());
          for (auto i = 1u; i <= num_file_toks; ++i) {
            auto p_tok = file.impl->tokens[num_file_toks - i];
            switch (p_tok.Kind()) {
              case clang::tok::unknown:
                continue;
              case clang::tok::at:
                i = num_file_toks;
                if (false) {}
#define OBJC_AT_KEYWORD(x) else if (ident == #x) { is_objc_keyword = 1; alt_keyword = static_cast<uint16_t>(clang::tok::objc_##x); }
#include <clang/Basic/TokenKinds.def>

              case clang::tok::hash:
                i = num_file_toks;
                if (false) {}
#define PPKEYWORD(x) else if (ident == #x) { is_pp_keyword = 1; alt_keyword = static_cast<uint16_t>(clang::tok::pp_##x); }
#include <clang/Basic/TokenKinds.def>

              default:
                i = num_file_toks;
                break;
            }
          }
        }
      }

      auto &last_tok = file.impl->tokens.emplace_back(
          offset,
          tok.getLength(),
          sm.getSpellingLineNumber(tok_loc),
          sm.getSpellingColumnNumber(tok_loc),
          tok_kind);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
      last_tok.kind.extended.is_pp_kw = is_pp_keyword;
      last_tok.kind.extended.is_objc_kw = is_objc_keyword;
      last_tok.kind.extended.alt_kind = alt_keyword;
#pragma GCC diagnostic pop
    }

    const auto tok_loc = tok.getLocation();
    file.impl->tokens.emplace_back(
        file.impl->data.size(), 0u, sm.getSpellingLineNumber(tok_loc),
        sm.getSpellingColumnNumber(tok_loc), clang::tok::eof);
  }
};

}  // namespace pasta
