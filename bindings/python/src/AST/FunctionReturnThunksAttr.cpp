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

void RegisterFunctionReturnThunksAttr(py::module_ &m) {
  py::class_<FunctionReturnThunksAttr, InheritableAttr>(m, "FunctionReturnThunksAttr")
    .def("__hash__", [](const FunctionReturnThunksAttr& attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const FunctionReturnThunksAttr& a, const FunctionReturnThunksAttr& b) { return a.RawAttr() == b.RawAttr(); })
    .def_property_readonly("spelling", &FunctionReturnThunksAttr::Spelling)
    .def_property_readonly("thunk_type", &FunctionReturnThunksAttr::ThunkType);
}
} // namespace pasta
