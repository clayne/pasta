/*
 * Copyright (c) 2021, Trail of Bits, Inc.
 *
 * This source code is licensed in accordance with the terms specified in
 * the LICENSE file found in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include <system_error>

#include <pasta/Util/FileSystem.h>
#include <pasta/Util/Result.h>

namespace pasta {

class AST;
class ASTImpl;
class Compiler;
class File;
class FileImpl;
class FileManagerImpl;
struct Stat;

// Manages one or more open files.
class FileManager {
 public:
  explicit FileManager(std::shared_ptr<class FileSystem> fs_);
  ~FileManager(void);

  // Return the file manager containing a file.
  static FileManager Containing(const File &file);

  // Return the file manager associated with a compiler.
  static FileManager From(const Compiler &file);

  // Try to open a file.
  Result<File, std::error_code> OpenFile(Stat stat) const;

  // Return the file system associated with this file manager.
  std::shared_ptr<::pasta::FileSystem> FileSystem(void) const;

 private:
  friend class Compiler;
  friend class File;
  friend class FileImpl;
  friend class FileManagerImpl;

  FileManager(void) = delete;

  inline explicit FileManager(std::shared_ptr<FileManagerImpl> impl_)
      : impl(std::move(impl_)) {}

  std::shared_ptr<FileManagerImpl> impl;
};

}  // namespace pasta
