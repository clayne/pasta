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

void RegisterBreakStmt(py::module_ &m) {
  py::class_<BreakStmt, Stmt>(m, "BreakStmt")
    .def("__hash__", [](const BreakStmt& stmt) { return (intptr_t)stmt.RawStmt(); })
    .def("__eq__", [](const Stmt& a, const Stmt& b) { return a.RawStmt() == b.RawStmt(); })
    .def_property_readonly("children", &BreakStmt::Children)
    .def_property_readonly("begin_token", &BreakStmt::BeginToken)
    .def_property_readonly("break_token", &BreakStmt::BreakToken)
    .def_property_readonly("end_token", &BreakStmt::EndToken);
}
} // namespace pasta
