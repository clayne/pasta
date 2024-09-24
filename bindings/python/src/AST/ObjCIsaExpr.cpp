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

void RegisterObjCIsaExpr(nb::module_ &m) {
  nb::class_<ObjCIsaExpr, Expr>(m, "ObjCIsaExpr")
    .def_prop_ro("children", &ObjCIsaExpr::Children)
    .def_prop_ro("base", &ObjCIsaExpr::Base)
    .def_prop_ro("base_token_end", &ObjCIsaExpr::BaseTokenEnd)
    .def_prop_ro("begin_token", &ObjCIsaExpr::BeginToken)
    .def_prop_ro("end_token", &ObjCIsaExpr::EndToken)
    .def_prop_ro("expression_token", &ObjCIsaExpr::ExpressionToken)
    .def_prop_ro("isa_member_token", &ObjCIsaExpr::IsaMemberToken)
    .def_prop_ro("operation_token", &ObjCIsaExpr::OperationToken)
    .def_prop_ro("is_arrow", &ObjCIsaExpr::IsArrow);
}
} // namespace pasta
