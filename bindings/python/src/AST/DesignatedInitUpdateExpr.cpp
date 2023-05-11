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

void RegisterDesignatedInitUpdateExpr(py::module_ &m) {
  py::class_<DesignatedInitUpdateExpr, Expr>(m, "DesignatedInitUpdateExpr")
    .def("__hash__", [](const DesignatedInitUpdateExpr& stmt) { return (intptr_t)stmt.RawStmt(); })
    .def("__eq__", [](const Stmt& a, const Stmt& b) { return a.RawStmt() == b.RawStmt(); })
    .def_property_readonly("children", &DesignatedInitUpdateExpr::Children)
    .def_property_readonly("base", &DesignatedInitUpdateExpr::Base)
    .def_property_readonly("begin_token", &DesignatedInitUpdateExpr::BeginToken)
    .def_property_readonly("end_token", &DesignatedInitUpdateExpr::EndToken)
    .def_property_readonly("updater", &DesignatedInitUpdateExpr::Updater);
}
} // namespace pasta
