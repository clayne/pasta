/*
 * Copyright (c) 2023, Trail of Bits, Inc.
 *
 * This source code is licensed in accordance with the terms specified in
 * the LICENSE file found in the root directory of this source tree.
 */

// This file is auto-generated.

#include <pasta/AST/AST.h>
#include <pasta/AST/Attr.h>
#include <pasta/AST/Decl.h>
#include <pasta/AST/Printer.h>
#include <pasta/AST/Stmt.h>
#include <pasta/AST/Token.h>
#include <pasta/AST/Type.h>

#include "../Bindings.h"

namespace pasta {
namespace nb = nanobind;

void RegisterCXXUuidofExpr(nb::module_ &m) {
  nb::class_<CXXUuidofExpr, Expr>(m, "CXXUuidofExpr")
    .def_prop_ro("children", &CXXUuidofExpr::Children)
    .def_prop_ro("begin_token", &CXXUuidofExpr::BeginToken)
    .def_prop_ro("end_token", &CXXUuidofExpr::EndToken)
    .def_prop_ro("expression_operand", &CXXUuidofExpr::ExpressionOperand)
    .def_prop_ro("guid_declaration", &CXXUuidofExpr::GuidDeclaration)
    .def_prop_ro("tokens", &CXXUuidofExpr::Tokens)
    .def_prop_ro("type_operand", &CXXUuidofExpr::TypeOperand)
    .def_prop_ro("type_operand_source_info", &CXXUuidofExpr::TypeOperandSourceInfo)
    .def_prop_ro("is_type_operand", &CXXUuidofExpr::IsTypeOperand);
}
} // namespace pasta
