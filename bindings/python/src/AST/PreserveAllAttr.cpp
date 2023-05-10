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

void RegisterPreserveAllAttr(py::module_ &m) {
  py::class_<PreserveAllAttr, InheritableAttr>(m, "PreserveAllAttr")
    .def("__hash__", [](const PreserveAllAttr& attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const PreserveAllAttr& a, const PreserveAllAttr& b) { return a.RawAttr() == b.RawAttr(); })
    .def_property_readonly("spelling", &PreserveAllAttr::Spelling);
}
} // namespace pasta
