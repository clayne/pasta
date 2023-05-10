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

void RegisterAssertCapabilityAttr(py::module_ &m) {
  py::class_<AssertCapabilityAttr, InheritableAttr>(m, "AssertCapabilityAttr")
    .def("__hash__", [](const AssertCapabilityAttr& attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const AssertCapabilityAttr& a, const AssertCapabilityAttr& b) { return a.RawAttr() == b.RawAttr(); })
    .def_property_readonly("semantic_spelling", &AssertCapabilityAttr::SemanticSpelling)
    .def_property_readonly("spelling", &AssertCapabilityAttr::Spelling)
    .def_property_readonly("is_shared", &AssertCapabilityAttr::IsShared);
}
} // namespace pasta
