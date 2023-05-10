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

void RegisterOMPTargetParallelDirective(py::module_ &m) {
  py::class_<OMPTargetParallelDirective, OMPExecutableDirective>(m, "OMPTargetParallelDirective")
    .def("__hash__", [](const OMPTargetParallelDirective& stmt) { return (intptr_t)stmt.RawStmt(); })
    .def("__eq__", [](const OMPTargetParallelDirective& a, const OMPTargetParallelDirective& b) { return a.RawStmt() == b.RawStmt(); })
    .def_property_readonly("task_reduction_reference_expression", &OMPTargetParallelDirective::TaskReductionReferenceExpression)
    .def_property_readonly("has_cancel", &OMPTargetParallelDirective::HasCancel);
}
} // namespace pasta
