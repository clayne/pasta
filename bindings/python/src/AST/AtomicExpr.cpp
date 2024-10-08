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

void RegisterAtomicExpr(nb::module_ &m) {
  nb::class_<AtomicExpr, Expr>(m, "AtomicExpr")
    .def_prop_ro("children", &AtomicExpr::Children)
    .def_prop_ro("begin_token", &AtomicExpr::BeginToken)
    .def_prop_ro("builtin_token", &AtomicExpr::BuiltinToken)
    .def_prop_ro("end_token", &AtomicExpr::EndToken)
    .def_prop_ro("num_sub_expressions", &AtomicExpr::NumSubExpressions)
    .def_prop_ro("operation", &AtomicExpr::Operation)
    .def_prop_ro("operation_as_string", &AtomicExpr::OperationAsString)
    .def_prop_ro("order", &AtomicExpr::Order)
    .def_prop_ro("order_fail", &AtomicExpr::OrderFail)
    .def_prop_ro("pointer", &AtomicExpr::Pointer)
    .def_prop_ro("r_paren_token", &AtomicExpr::RParenToken)
    .def_prop_ro("scope", &AtomicExpr::Scope)
    .def_prop_ro("value1", &AtomicExpr::Value1)
    .def_prop_ro("value2", &AtomicExpr::Value2)
    .def_prop_ro("value_type", &AtomicExpr::ValueType)
    .def_prop_ro("weak", &AtomicExpr::Weak)
    .def_prop_ro("is_cmp_x_chg", &AtomicExpr::IsCmpXChg)
    .def_prop_ro("is_open_cl", &AtomicExpr::IsOpenCL)
    .def_prop_ro("is_volatile", &AtomicExpr::IsVolatile);
}
} // namespace pasta
