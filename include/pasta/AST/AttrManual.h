/*
 * Copyright (c) 2022, Trail of Bits, Inc.
 *
 * This source code is licensed in accordance with the terms specified in
 * the LICENSE file found in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include <optional>

#include "Forward.h"

namespace clang {
class Attr;
class AttributeCommonInfo;
}  // namespace clang
namespace pasta {

class Attr;
class TokenContext;

enum class AttributeSyntax : unsigned int {
  GNU,
  CXX11,
  C2x,
  Declspec,
  Microsoft,
  Keyword,
  Pragma,
  ContextSensitiveKeyword,
};

class AttributeCommonInfo {
 private:
  std::shared_ptr<ASTImpl> ast;
  const clang::Attr *attr;

  friend class Attr;
 public:
  inline AttributeCommonInfo(std::shared_ptr<ASTImpl> ast_,
                             const clang::Attr &attr_)
      : ast(std::move(ast_)), attr(&attr_) {}

  inline AttributeCommonInfo(std::shared_ptr<ASTImpl> ast_,
                             const clang::Attr *attr_)
      : ast(std::move(ast_)), attr(attr_) {}

#ifndef PASTA_IN_BOOTSTRAP
  inline const void *RawAttr(void) const noexcept {
    return attr;
  }

  // Returns attribute syntax
  AttributeSyntax Syntax() const noexcept;

  // Is declspec syntax?
  bool IsDeclspecAttribute() const noexcept;

  // Is microsoft syntax?
  bool IsMicrosoftAttribute() const noexcept;

  // Is GNU syntax?
  bool IsGNUScope() const noexcept;

  // Is CXX11 attribute?
  bool IsCXX11Attribute() const noexcept;

  // Is C2x attribute?
  bool IsC23Attribute() const noexcept;

  // Is keyword attribute?
  bool IsKeywordAttribute() const noexcept;

  // Is context-sensitive keyword attribute?
  bool IsContextSensitiveKeywordAttribute() const noexcept;

  // The attribute is spelled `[[]]` in either C or C++ mode, including standard
  // attributes spelled with a keyword, like `alignas`.
  inline bool isStandardAttributeSyntax() const {
    return IsCXX11Attribute() || IsC23Attribute();
  }
#endif
};

}

