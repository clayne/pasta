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

void RegisterPcsAttr(py::module_ &m) {
  py::class_<PcsAttr, InheritableAttr>(m, "PcsAttr")
    .def("__hash__", [](const PcsAttr& attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const Attr& a, const Attr& b) { return a.RawAttr() == b.RawAttr(); })
    .def_property_readonly("pcs", &PcsAttr::PCS)
    .def_property_readonly("spelling", &PcsAttr::Spelling);
}
} // namespace pasta
