/*
 * Copyright (c) 2023 Trail of Bits, Inc.
 */

// This file is auto-generated.

#include <pasta/AST/AST.h>
#include <pasta/AST/Attr.h>
#include <pasta/AST/Decl.h>
#include <pasta/AST/Stmt.h>
#include <pasta/AST/Type.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace pasta {
namespace py = pybind11;

void RegisterImplicitCastExpr(py::module_ &m) {
  py::class_<ImplicitCastExpr, CastExpr>(m, "ImplicitCastExpr")
    .def("__hash__", [](const ImplicitCastExpr& stmt) { return (intptr_t)stmt.RawStmt(); })
    .def("__eq__", [](const Stmt& a, const Stmt& b) { return a.RawStmt() == b.RawStmt(); })
    .def_property_readonly("begin_token", &ImplicitCastExpr::BeginToken)
    .def_property_readonly("end_token", &ImplicitCastExpr::EndToken)
    .def_property_readonly("is_part_of_explicit_cast", &ImplicitCastExpr::IsPartOfExplicitCast);
}
} // namespace pasta
