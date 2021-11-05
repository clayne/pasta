/*
 * Copyright (c) 2021 Trail of Bits, Inc.
 */

#include <pasta/AST/AST.h>
#include <pasta/AST/Decl.h>
#include <pasta/Compile/Command.h>
#include <pasta/Compile/Compiler.h>
#include <pasta/Compile/Job.h>
#include <pasta/Util/ArgumentVector.h>
#include <pasta/Util/FileSystem.h>
#include <pasta/Util/Init.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include "../../include/pasta/AST/Printer.h"

class ASTDumper final : public pasta::DeclVisitor {
 public:
  virtual ~ASTDumper(void) = default;

  explicit ASTDumper(const pasta::AST &ast_, std::ostream &os_)
      : ast(ast_),
        os(os_) {}

  pasta::AST ast;
  std::ostream &os;

  void VisitDeclContext(const pasta::DeclContext &dc) {
    for (const auto &decl : dc.AlreadyLoadedDecls()) {
      Accept(decl);
    }
  }

  void VisitTranslationUnitDecl(const pasta::TranslationUnitDecl &decl) final {
    VisitDeclContext(decl);
  }

  void VisitNamespaceDecl(const pasta::NamespaceDecl &decl) final {
    VisitDeclContext(decl);
  }

  void VisitExternCContextDecl(const pasta::ExternCContextDecl &decl) final {
    VisitDeclContext(decl);
  }


  void VisitDecl(const pasta::Decl &decl) final {
    os << decl.KindName() << "\n";

    auto tokens = pasta::PrintedTokenRange::Create(decl);
    for (pasta::PrintedToken tok : tokens) {
      for (auto i = 0u, max_i = tok.NumLeadingNewLines(); i < max_i; ++i) {
        std::cerr << '\n';
      }
      for (auto i = 0u, max_i = tok.NumleadingSpaces(); i < max_i; ++i) {
        std::cerr << ' ';
      }
      std::cerr << tok.Data();
    }

    std::cerr << "\n\n";
  }
};

static void DumpAST(pasta::AST ast) {
  ASTDumper dumper(ast, std::cerr);
  dumper.Accept(ast.TranslationUnit());
}

int main(int argc, char *argv[]) {
  if (2 > argc) {
    std::cerr << "Usage: " << argv[0] << " COMPILE_COMMAND..."
              << std::endl;
    return EXIT_FAILURE;
  }

  pasta::InitPasta initializer;
  pasta::FileManager fm(pasta::FileSystem::CreateNative());
  auto maybe_compiler =
      pasta::Compiler::CreateHostCompiler(fm, pasta::TargetLanguage::kCXX);
  if (maybe_compiler.Failed()) {
    std::cerr << maybe_compiler.TakeError() << std::endl;
    return EXIT_FAILURE;
  }

  auto maybe_cwd = maybe_compiler->FileSystem()->CurrentWorkingDirectory();
  if (maybe_cwd.Failed()) {
    std::cerr << maybe_compiler.TakeError() << std::endl;
    return EXIT_FAILURE;
  }

  const pasta::ArgumentVector args(argc - 1, &argv[1]);
  auto maybe_command = pasta::CompileCommand::CreateFromArguments(
      args, maybe_cwd.TakeValue());
  if (maybe_command.Failed()) {
    std::cerr << maybe_command.TakeError() << std::endl;
    return EXIT_FAILURE;
  }

  const auto command = std::move(*maybe_command);
  auto maybe_jobs = maybe_compiler->CreateJobsForCommand(command);
  if (maybe_jobs.Failed()) {
    std::cerr << maybe_jobs.TakeError() << std::endl;
    return EXIT_FAILURE;
  }

  for (const auto &job : *maybe_jobs) {
    auto maybe_ast = job.Run();
    if (maybe_ast.Failed()) {
      std::cerr << maybe_ast.TakeError() << std::endl;
      return EXIT_FAILURE;
    } else {
      DumpAST(*maybe_ast);
    }
  }

  return EXIT_SUCCESS;
}

