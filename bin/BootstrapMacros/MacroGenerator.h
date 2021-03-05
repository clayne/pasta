/*
 * Copyright (c) 2021 Trail of Bits, Inc.
 */

#pragma once

#include <map>
#include <unordered_set>
#include <sstream>
#include <string>

#include <clang/AST/RecursiveASTVisitor.h>

namespace pasta {

class MacroGenerator : public clang::RecursiveASTVisitor<MacroGenerator> {
 public:
  MacroGenerator(const clang::ASTContext *ctx);

  ~MacroGenerator(void);

  bool VisitEnumDecl(clang::EnumDecl *decl);
  bool VisitCXXRecordDecl(clang::CXXRecordDecl *decl);

 private:
  const clang::ASTContext *context;
  std::unordered_set<std::string> acceptable_class_names;
  std::unordered_set<std::string> unacceptable_enum_names;
  std::map<std::string, clang::CXXRecordDecl *> decl_classes;
  std::map<std::string, clang::EnumDecl *> decl_enums;
};

}  // namespace pasta