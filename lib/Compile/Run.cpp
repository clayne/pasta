/*
 * Copyright (c) 2020 Trail of Bits, Inc.
 */

#include "AST.h"
#include "Compiler.h"
#include "Diagnostic.h"
#include "Job.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-int-conversion"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#include <clang/AST/ASTConsumer.h>
#include <clang/Basic/Diagnostic.h>
#include <clang/Basic/DiagnosticIDs.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Parse/Parser.h>
#include <clang/Sema/Sema.h>
#include <llvm/Support/VirtualFileSystem.h>
#pragma clang diagnostic pop

#include <pasta/Util/ArgumentVector.h>

namespace pasta {

// Run a command ans return the AST or the first error.
llvm::Expected<AST> CompileJob::Run(void) const {
  auto ast = std::make_shared<ASTImpl>();
  llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> real_vfs(
      llvm::vfs::createPhysicalFileSystem().release());
  llvm::IntrusiveRefCntPtr<llvm::vfs::OverlayFileSystem> overlay_vfs(
      new llvm::vfs::OverlayFileSystem(real_vfs.get()));
  llvm::IntrusiveRefCntPtr<llvm::vfs::InMemoryFileSystem> mem_vfs(
      new llvm::vfs::InMemoryFileSystem);
  overlay_vfs->pushOverlay(mem_vfs.get());
  overlay_vfs->setCurrentWorkingDirectory(WorkingDirectory().data());

  auto diag = new SaveFirstErrorDiagConsumer;
  auto ci = std::make_shared<clang::CompilerInstance>();
  llvm::IntrusiveRefCntPtr<clang::DiagnosticsEngine> diagnostics_engine(
      new clang::DiagnosticsEngine(new clang::DiagnosticIDs,
                                   new clang::DiagnosticOptions, diag,
                                   false /* Take ownership of the consumer */));

  diagnostics_engine->Reset();
  diagnostics_engine->setIgnoreAllWarnings(true);
  diagnostics_engine->setWarningsAsErrors(false);

  ci->setDiagnostics(diagnostics_engine.get());
  ci->setASTConsumer(std::make_unique<clang::ASTConsumer>());

  auto &invocation = ci->getInvocation();
  auto &fs_options = invocation.getFileSystemOpts();
  fs_options.WorkingDir = WorkingDirectory();

  llvm::IntrusiveRefCntPtr<clang::FileManager> fm(
      new clang::FileManager(fs_options, overlay_vfs.get()));

  ci->setFileManager(fm.get());
  ci->createSourceManager(*fm);

  // Make sure the compiler instance is starting with the approximately
  // the right cross-compilation target info.
  auto &target_opts = invocation.getTargetOpts();
  target_opts.HostTriple = llvm::sys::getDefaultTargetTriple();
  target_opts.Triple = TargetTriple();
  ci->setTarget(clang::TargetInfo::CreateTargetInfo(ci->getDiagnostics(),
                                                    invocation.TargetOpts));

  const auto &argv = Arguments();
  const auto invocation_is_valid = clang::CompilerInvocation::CreateFromArgs(
      invocation, argv.Argv(), &(argv.Argv()[argv.Size()]),
      *diagnostics_engine);

  if (!invocation_is_valid) {
    if (diag->error.empty()) {
      return llvm::createStringError(
          std::make_error_code(std::errc::invalid_argument),
          "Unable to create compiler invocation from command: %s",
          argv.Join().c_str());
    } else {
      return llvm::createStringError(
          std::make_error_code(std::errc::invalid_argument),
          "Unable to create compiler invocation from command: %s",
          diag->error.c_str());
    }
  }

  // Just in case parsing of the command-line args changed this.
  diagnostics_engine->setConstexprBacktraceLimit(0);
  diagnostics_engine->setTemplateBacktraceLimit(0);
  diagnostics_engine->setErrorLimit(1);
  diagnostics_engine->setIgnoreAllWarnings(true);
  diagnostics_engine->setWarningsAsErrors(false);

  // TODO(pag): Consider setting `UsePredefines` to `false` and using an
  //            `-include` file generated by `mu-import` to deal with platform
  //            and compiler differences.
  //
  // TODO(pag): Generate said pre-define include file.
  //
  // TODO(pag): We can possibly also emit implicitly generated functions
  //            and typedefs (via pretty printing) to this file, and also
  //            disable their generation. This will then hopefully mean
  //            fewer implicit decls in the indexer.
  auto &pp_options = invocation.getPreprocessorOpts();
  pp_options.DetailedRecord = true;
  pp_options.SingleFileParseMode = false;
  pp_options.LexEditorPlaceholders = false;
  pp_options.RetainRemappedFileBuffers = true;

  auto &ppo_options = invocation.getPreprocessorOutputOpts();
  ppo_options = {};  // Reset to defaults.

  const auto lang_opts = invocation.getLangOpts();

  lang_opts->EmitAllDecls = true;
  lang_opts->CXXExceptions = true;
  lang_opts->Blocks = true;
  lang_opts->POSIXThreads = true;
  lang_opts->HeinousExtensions = true;
  lang_opts->DoubleSquareBracketAttributes = true;
  lang_opts->GNUMode = true;
  lang_opts->GNUKeywords = true;
  lang_opts->GNUAsm = true;
  lang_opts->SpellChecking = false;
  lang_opts->RetainCommentsFromSystemHeaders = false;
  lang_opts->AllowEditorPlaceholders = false;
  lang_opts->CommentOpts.ParseAllComments = false;

  // Affects `PPCallbacks`, and also does additional parsing of things in
  // Objective-C mode, e.g. parsing module imports.
  lang_opts->DebuggerSupport = true;

  // TODO(pag): Should pragmas be ignored?

  // Enable C++-style comments, even in C code. If we don't do this, then we
  // can observe two tokens for something like `// foo` in C code, one is a
  // `slash`, the second is a `comment`.
  lang_opts->LineComment = true;

  // Don't get whitespace.
  lang_opts->TraditionalCPP = false;

  auto &frontend_opts = invocation.getFrontendOpts();
  frontend_opts.StatsFile.clear();
  frontend_opts.OverrideRecordLayoutsFile.clear();
  frontend_opts.ASTDumpFilter.clear();

  // TODO(pag): Eventually support? A better way would be to load them into
  //            `Compiler` or into `CompileCommand`.
  frontend_opts.Plugins.clear();
  frontend_opts.ActionName.clear();
  frontend_opts.PluginArgs.clear();
  frontend_opts.AddPluginActions.clear();

  // Go check that we've got an input file, them initialize the source manager
  // with the first input file.
  auto &input_files = frontend_opts.Inputs;
  if (input_files.empty()) {
    return llvm::createStringError(
        std::make_error_code(std::errc::no_such_file_or_directory),
        "No input file in compilation command: %s", argv.Join().c_str());

  // There should only be one input files, as we're dealing with `-cc1`
  // commands, not frontend commands.
  } else if (1u < input_files.size()) {
    return llvm::createStringError(
        std::make_error_code(std::errc::too_many_files_open),
        "Too many input files in compilation command: %s", argv.Join().c_str());
  }

  auto &invocation_target = ci->getTarget();

  // Create TargetInfo for the other side of CUDA and OpenMP compilation.
  if ((lang_opts->CUDA || lang_opts->OpenMPIsDevice) &&
      !frontend_opts.AuxTriple.empty()) {
    auto aux_target = std::make_shared<clang::TargetOptions>();
    aux_target->Triple = llvm::Triple::normalize(frontend_opts.AuxTriple);
    aux_target->HostTriple = invocation_target.getTriple().str();
    ci->setAuxTarget(
        clang::TargetInfo::CreateTargetInfo(*diagnostics_engine, aux_target));
  }

  invocation_target.adjust(*lang_opts);
  invocation_target.adjustTargetOptions(ci->getCodeGenOpts(),
                                        ci->getTargetOpts());

  if (auto aux_target = ci->getAuxTarget(); aux_target) {
    invocation_target.setAuxTarget(aux_target);
  }

  // Clear out any dependency file stuff. Sometimes the paths for the depdency
  // files are incorrect, and that shouldn't hold up a build.
  auto &dep_opts = ci->getDependencyOutputOpts();
  dep_opts = clang::DependencyOutputOptions();

  // TODO(pag): Eventually add `PPCallbacks` so that we can capture macro
  //            definitions as tokens.

  ci->createPreprocessor(clang::TU_Complete);
  auto &pp = ci->getPreprocessor();

  pp.SetCommentRetentionState(false /* KeepComments */,
                              false /* KeepMacroComments */);

  pp.getBuiltinInfo().initializeBuiltins(pp.getIdentifierTable(), *lang_opts);
  pp.setPragmasEnabled(true);

  // Picks up on the pre-processor and stuff.
  ci->InitializeSourceManager(input_files[0]);
  ci->createASTContext();
  ci->createSema(clang::TU_Complete, nullptr);

  //auto &source_manager = ci->getSourceManager();
  auto &ast_context = ci->getASTContext();
  auto &ast_consumer = ci->getASTConsumer();
  auto &sema = ci->getSema();

  std::unique_ptr<clang::Parser> parser(
      new clang::Parser(pp, sema, false /* SkipFunctionBodies */));

  pp.EnterMainSourceFile();
  parser->Initialize();

  clang::Parser::DeclGroupPtrTy a_decl;
  for (auto at_eof = parser->ParseFirstTopLevelDecl(a_decl); !at_eof;
       at_eof = parser->ParseTopLevelDecl(a_decl)) {

    // Parsing a dangling top-level semicolon will result in a null declaration.
    if (a_decl && !ast_consumer.HandleTopLevelDecl(a_decl.get())) {
      break;
    }
  }

  // Process any TopLevelDecls generated by #pragma weak.
  for (auto decl : sema.WeakTopLevelDecls()) {
    if (decl && !ast_consumer.HandleTopLevelDecl(clang::DeclGroupRef(decl))) {
      break;
    }
  }

  // Finalize any leftover instantiations.
  sema.PerformPendingInstantiations(false);

  if (diagnostics_engine->hasUncompilableErrorOccurred() ||
      diagnostics_engine->hasFatalErrorOccurred()) {
    if (diag->error.empty()) {
      return llvm::createStringError(
          std::make_error_code(std::errc::invalid_argument),
          "A clang diagnostic or uncompilable error was produced when trying "
          "to get an AST from the command: %s",
          argv.Join().c_str());

    } else {
      return llvm::createStringError(
          std::make_error_code(std::errc::invalid_argument),
          "A clang diagnostic or uncompilable error was produced when trying "
          "to get an AST: %s",
          diag->error.c_str());
    }
  }

  ast->real_fs = std::move(real_vfs);
  ast->overlay_fs = std::move(overlay_vfs);
  ast->mem_fs = std::move(mem_vfs);
  ast->ci = std::move(ci);
  ast->fm = std::move(fm);
  ast->tu = ast_context.getTranslationUnitDecl();

  return AST(std::move(ast));
}

}  // namespace pasta
