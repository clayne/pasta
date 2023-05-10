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

void RegisterDependentSizedMatrixType(py::module_ &m) {
  py::class_<DependentSizedMatrixType, MatrixType>(m, "DependentSizedMatrixType")
    .def("__hash__", [](const DependentSizedMatrixType& type) { return (intptr_t)type.RawType(); })
    .def("__eq__", [](const DependentSizedMatrixType& a, const DependentSizedMatrixType& b) { return a.RawType() == b.RawType(); })
    .def_property_readonly("attribute_token", &DependentSizedMatrixType::AttributeToken)
    .def_property_readonly("column_expression", &DependentSizedMatrixType::ColumnExpression)
    .def_property_readonly("row_expression", &DependentSizedMatrixType::RowExpression);
}
} // namespace pasta
