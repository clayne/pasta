/*
 * Copyright (c) 2020 Trail of Bits, Inc.
 */

#pragma once

#include <pasta/Compile/Command.h>
#include <pasta/Compile/Compiler.h>
#include <pasta/Compile/Job.h>
#include <pasta/Python/Bindings.h>

#include <optional>

namespace pasta {
namespace py {

template <>
struct StorageType<CompilerName> {
 public:
  using Type = EnumWrapper<CompilerName, unsigned>;
};

template <>
struct StorageType<TargetLanguage> {
 public:
  using Type = EnumWrapper<TargetLanguage, unsigned>;
};

DEFINE_PYTHON_ARG(target_language, TargetLanguage);
DEFINE_PYTHON_ARG(compiler_name, CompilerName);
DEFINE_PYTHON_ARG(compiler_path, std::string_view);
DEFINE_PYTHON_ARG(version_info, std::string_view);
DEFINE_PYTHON_KWARG(working_dir, std::string_view);
DEFINE_PYTHON_ARG(file_path, std::string_view);

// Return the current working directory.
std::string CurrentWorkingDir(const working_dir_kwarg &working_dir);

// A single backend compilation job. There is a one to many relationship
// between `CompileCommand`s and `CompilerJob`s, as a single compile command
// may actually reference multiple source files, whereas a compilation job
// references only one.
class CompileJob : public PythonObject<::pasta::py::CompileJob> {
 public:
  // Tries to add the `CompileJob` type to the `pasta` module.
  static bool TryAddToModule(PyObject *module);

  ~CompileJob(void);
  DEFINE_PYTHON_CONSTRUCTOR(CompileJob, void);

  inline CompileJob(::pasta::CompileJob job_) : job(std::move(job_)) {}

  // Return an argument vector associated with this compilation job.
  std::vector<std::string_view> Arguments(void);

  // Return the working directory in which this command executes.
  std::string_view WorkingDirectory(void);

  // Return the compiler resource directory that this command should use.
  std::string_view ResourceDirectory(void);

  // Return the compiler system root directory that this command should use.
  std::string_view SystemRootDirectory(void);

  // Return the target triple to use.
  std::string_view TargetTriple(void);

  // Return the auxiliary target triple to use.
  std::string_view AuxiliaryTargetTriple(void);

  // Return the path to the source file that this job compiles.
  std::string_view SourceFile(void);

  //  // Run a backend compilation job and returns the AST or the first error.
  //  llvm::Expected<AST> Run(void);

  std::optional<::pasta::CompileJob> job;
};

// A high-level compile command. This is a frontent compile command. It may
// include multiple files.
class CompileCommand : public PythonObject<::pasta::py::CompileCommand> {
 public:
  // Tries to add the `CompileCommand` type to the `pasta` module.
  static bool TryAddToModule(PyObject *module);

  ~CompileCommand(void);

  inline CompileCommand(::pasta::CompileCommand command_)
      : command(std::move(command_)) {}

  DEFINE_PYTHON_ARG(command, std::vector<std::string>);
  DEFINE_PYTHON_CONSTRUCTOR(CompileCommand, command_arg command,
                            working_dir_kwarg working_dir);

  // Return an argument vector associated with this compilation command.
  std::vector<std::string_view> Arguments(void);

  // Return the working directory in which this command executes.
  std::string_view WorkingDirectory(void);

  std::optional<::pasta::CompileCommand> command;
};

class Compiler : public PythonObject<::pasta::py::Compiler> {
 public:
  // Tries to add the `Compiler` type to the `pasta` module.
  static bool TryAddToModule(PyObject *module);

  ~Compiler(void);

  DEFINE_PYTHON_CONSTRUCTOR(Compiler, compiler_name_arg name,
                            target_language_arg lang,
                            compiler_path_arg compiler_path,
                            version_info_arg version_info,
                            working_dir_kwarg working_dir);

  // Name/variant of this compiler.
  unsigned Name(void);

  // Target language for this compiler.
  unsigned TargetLanguage(void);

  // Path to the executable.
  std::string_view ExecutablePath(void);

  // Resource directory of the compiler, i.e. where you find compiler-specific
  // header files.
  std::string_view ResourceDirectory(void);

  // Directory to treat as the system root. Useful for cross-compilation
  // toolchains.
  std::string_view SystemRootDirectory(void);

  // Directory where the compiler is installed.
  std::string_view InstallationDirectory(void);

  // List of system include directories.
  const std::vector<std::string_view> SystemIncludeDirectories(void);

  // List of user include directories.
  const std::vector<std::string_view> UserIncludeDirectories(void);

  // List of framework directories.
  const std::vector<std::string_view> FrameworkDirectories(void);

  // Create a compile command for a single file in a working directory.
  BorrowedPythonPtr<CompileCommand>
  CreateCommandForFile(file_path_arg file_path, working_dir_kwarg working_dir);

  DEFINE_PYTHON_ARG(command, BorrowedPythonPtr<CompileCommand>);

  // Create a compile command for a single file in a working directory.
  std::vector<BorrowedPythonPtr<CompileJob>>
  CreateJobsForCommand(command_arg command);

  std::optional<::pasta::Compiler> compiler;
};

}  // namespace py
}  // namespace pasta
