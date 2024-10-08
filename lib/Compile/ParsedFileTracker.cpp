/*
 * Copyright (c) 2022, Trail of Bits, Inc.
 *
 * This source code is licensed in accordance with the terms specified in
 * the LICENSE file found in the root directory of this source tree.
 */

#include "ParsedFileTracker.h"

namespace pasta {

ParsedFileTracker::~ParsedFileTracker(void) {}

void ParsedFileTracker::Clear(void) {
  fs.reset();
}

void ParsedFileTracker::AddEOF(File &file, clang::FileID file_id,
                               clang::SourceManager &sm) {
  clang::Token tok;
  tok.startToken();
  tok.setKind(clang::tok::eof);
  tok.setLocation(sm.getLocForEndOfFile(file_id));

  assert(!file.impl->data.empty());
  assert(file.impl->data.back() == '\0');
  const auto tok_loc = tok.getLocation();
  file.impl->tokens.emplace_back(
      file.impl->data.size() - 1u,
      0u,
      sm.getSpellingLineNumber(tok_loc),
      sm.getSpellingColumnNumber(tok_loc), clang::tok::eof);
}

// Each time we enter a source file, try to keep track of it.
void ParsedFileTracker::FileChanged(clang::SourceLocation loc,
                 clang::PPCallbacks::FileChangeReason reason,
                 clang::SrcMgr::CharacteristicKind file_type,
                 clang::FileID file_id) {

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

  auto fe = sm.getFileEntryRefForID(file_id);
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
  auto raw_file_id = file_id.getHashValue();
  auto [file_it, added] = ast->id_to_file.emplace(raw_file_id, file);
  assert(file_it->second.impl.get() == file.impl.get());

  // If we've seen this file already, then don't tokenize it.
  if (!added) {
    return;
  }

  auto file_index = static_cast<unsigned>(ast->parsed_files.size());
  ast->parsed_files.emplace_back(file);
  ast->id_to_file_offset.emplace(raw_file_id, file_index);

  auto maybe_data = file.Data();
  if (!maybe_data.Succeeded()) {
    return;
  }

  std::unique_lock<std::mutex> locker(file.impl->tokens_lock);
  if (file.impl->has_tokens) {
    return;
  }

  auto data = maybe_data.TakeValue();
  file.impl->has_tokens = true;
  const size_t buff_size = data.size();
  if (!buff_size) {
    // NOTE(pag): The file already has a trailing `\0`, but doesn't include it
    //            in `data`.
    AddEOF(file, file_id, sm);
    return;
  }

  const char * const buff_begin = &(data.front());
  const char * const buff_end = &(buff_begin[buff_size]);

  // Note(kumarak): Check if the file buffer starts with
  //                byte-offset marker. If yes then add
  //                an unknown token of length 3.
  // I expect lexer to look for token at offset 0 or 3 and
  // not in between. If that is a possibility add different
  // token for each bytes.
  if (HasBOM(buff_begin, buff_size)) {
    auto adjusted_offset = 3u;
    file.impl->tokens.emplace_back(
        0u,
        adjusted_offset,
        0u,
        0u,
        clang::tok::unknown);
  }

  clang::Lexer lexer(loc, lang_opts, buff_begin, buff_begin, buff_end);
  lexer.SetKeepWhitespaceMode(true);  // Implies keep comments.

  // Raw lex this file's tokens.
  clang::Token tok;
  auto has_more_buffer = true;
  do {
    has_more_buffer = !lexer.LexFromRawLexer(tok);
    assert(!tok.hasLeadingEmptyMacro());
    assert(!tok.isAnnotation());
    if (tok.is(clang::tok::eof)) {
      break;
    }
    
    clang::SourceLocation tok_loc = tok.getLocation();
    const auto offset = sm.getFileOffset(tok_loc);
    const auto len = tok.getLength();
    assert(offset < buff_size);
    assert((offset + tok.getLength()) <= buff_size);
    auto tok_kind = tok.getKind();

    uint16_t is_pp_keyword = 0;
    uint16_t is_objc_keyword = 0;
    uint16_t alt_keyword = 0;

    clang::SourceLocation fixed_loc = tok_loc;
    auto fixed_offset = offset;
    auto fixed_len = len;

    // Skip over leading whitespace if this isn't a whitespace token.
    for (auto skip = true; skip && fixed_len && fixed_offset < buff_size; ) {
      skip = false;
      switch (buff_begin[fixed_offset]) {
        case '\r':
          assert(false);
          [[fallthrough]];
        case '\\':
        case ' ':
        case '\t':
        case '\n':
          ++fixed_offset;
          --fixed_len;
          fixed_loc = fixed_loc.getLocWithOffset(1);
          skip = true;
          break;
        default:
          skip = false;
          break;
      }
    }

    // There was leading whitespace, go and form a token for it.
    if (auto diff = fixed_offset - offset) {
      assert(diff < len || (diff == len && clang::tok::unknown == tok_kind));
      auto has_nl = false;
      auto num_non_nl_endings = 0u;
      for (auto i = offset; i < fixed_offset; ++i) {
        switch (buff_begin[i]) {
          case '\r':
          case '\\':
          case '\n':
            has_nl = true;
            num_non_nl_endings = 0;
            break;
          case ' ':
          case '\t':
            ++num_non_nl_endings;
            break;
          default:
            assert(false);
            num_non_nl_endings = 0;
            break;
        }
      }

      // Break the whitespace into two: the leading part with newlines, and the
      // trailing part with only indentation.
      if (has_nl && num_non_nl_endings) {
        file.impl->tokens.emplace_back(
            offset,
            (diff - num_non_nl_endings),
            sm.getSpellingLineNumber(tok_loc),
            sm.getSpellingColumnNumber(tok_loc),
            clang::tok::unknown);

        tok_loc = tok_loc.getLocWithOffset(
            static_cast<int>(diff - num_non_nl_endings));

        file.impl->tokens.emplace_back(
            offset + (diff - num_non_nl_endings),
            num_non_nl_endings,
            sm.getSpellingLineNumber(tok_loc),
            sm.getSpellingColumnNumber(tok_loc),
            clang::tok::unknown);

      // Add in a whitespace token.
      } else {
        file.impl->tokens.emplace_back(
            offset,
            diff,
            sm.getSpellingLineNumber(tok_loc),
            sm.getSpellingColumnNumber(tok_loc),
            clang::tok::unknown);
      }

      // Fixup the token to no longer include the leading whitespace.
      tok.setLocation(fixed_loc);
      tok.setLength(tok.getLength() - diff);
    }

    if (clang::tok::unknown == tok_kind) {
      continue;
    }

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
        fixed_offset,
        fixed_len,
        sm.getSpellingLineNumber(fixed_loc),
        sm.getSpellingColumnNumber(fixed_loc),
        tok_kind);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
    last_tok.kind.extended.is_pp_kw = is_pp_keyword;
    last_tok.kind.extended.is_objc_kw = is_objc_keyword;
    last_tok.kind.extended.alt_kind = alt_keyword;
#pragma GCC diagnostic pop
  } while (has_more_buffer);

  AddEOF(file, file_id, sm);
}

}  // namespace pasta
