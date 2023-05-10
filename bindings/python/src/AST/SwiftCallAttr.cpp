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

void RegisterSwiftCallAttr(py::module_ &m) {
  py::class_<SwiftCallAttr, InheritableAttr>(m, "SwiftCallAttr")
    .def("__hash__", [](const SwiftCallAttr& attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const SwiftCallAttr& a, const SwiftCallAttr& b) { return a.RawAttr() == b.RawAttr(); })
    .def_property_readonly("spelling", &SwiftCallAttr::Spelling);
}
} // namespace pasta
