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

void RegisterPtr32Attr(py::module_ &m) {
  py::class_<Ptr32Attr, TypeAttr>(m, "Ptr32Attr")
    .def("__hash__", [](const Ptr32Attr& attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const Ptr32Attr& a, const Ptr32Attr& b) { return a.RawAttr() == b.RawAttr(); })
    .def_property_readonly("spelling", &Ptr32Attr::Spelling);
}
} // namespace pasta
