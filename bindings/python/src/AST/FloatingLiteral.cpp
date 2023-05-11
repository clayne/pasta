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

void RegisterFloatingLiteral(py::module_ &m) {
  py::class_<FloatingLiteral, Expr>(m, "FloatingLiteral")
    .def("__hash__", [](const FloatingLiteral& stmt) { return (intptr_t)stmt.RawStmt(); })
    .def("__eq__", [](const Stmt& a, const Stmt& b) { return a.RawStmt() == b.RawStmt(); })
    .def_property_readonly("children", &FloatingLiteral::Children)
    .def_property_readonly("begin_token", &FloatingLiteral::BeginToken)
    .def_property_readonly("end_token", &FloatingLiteral::EndToken)
    .def_property_readonly("token", &FloatingLiteral::Token)
    .def_property_readonly("value_as_approximate_double", &FloatingLiteral::ValueAsApproximateDouble)
    .def_property_readonly("is_exact", &FloatingLiteral::IsExact);
}
} // namespace pasta
