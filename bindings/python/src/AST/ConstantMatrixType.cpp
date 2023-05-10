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

void RegisterConstantMatrixType(py::module_ &m) {
  py::class_<ConstantMatrixType, MatrixType>(m, "ConstantMatrixType")
    .def("__hash__", [](const ConstantMatrixType& type) { return (intptr_t)type.RawType(); })
    .def("__eq__", [](const ConstantMatrixType& a, const ConstantMatrixType& b) { return a.RawType() == b.RawType(); })
    .def_property_readonly("num_columns", &ConstantMatrixType::NumColumns)
    .def_property_readonly("num_elements_flattened", &ConstantMatrixType::NumElementsFlattened)
    .def_property_readonly("num_rows", &ConstantMatrixType::NumRows);
}
} // namespace pasta
