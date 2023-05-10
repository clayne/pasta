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

void RegisterCapabilityAttr(py::module_ &m) {
  py::class_<CapabilityAttr, InheritableAttr>(m, "CapabilityAttr")
    .def("__hash__", [](const CapabilityAttr& attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const CapabilityAttr& a, const CapabilityAttr& b) { return a.RawAttr() == b.RawAttr(); })
    .def_property_readonly("name", &CapabilityAttr::Name)
    .def_property_readonly("name_length", &CapabilityAttr::NameLength)
    .def_property_readonly("semantic_spelling", &CapabilityAttr::SemanticSpelling)
    .def_property_readonly("spelling", &CapabilityAttr::Spelling)
    .def_property_readonly("is_shared", &CapabilityAttr::IsShared);
}
} // namespace pasta
