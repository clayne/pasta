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

void RegisterOpenCLPrivateAddressSpaceAttr(py::module_ &m) {
  py::class_<OpenCLPrivateAddressSpaceAttr, TypeAttr>(m, "OpenCLPrivateAddressSpaceAttr")
    .def("__hash__", [](const OpenCLPrivateAddressSpaceAttr& attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const Attr& a, const Attr& b) { return a.RawAttr() == b.RawAttr(); })
    .def_property_readonly("semantic_spelling", &OpenCLPrivateAddressSpaceAttr::SemanticSpelling)
    .def_property_readonly("spelling", &OpenCLPrivateAddressSpaceAttr::Spelling);
}
} // namespace pasta
