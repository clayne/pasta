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

void RegisterOMPMasterTaskLoopDirective(py::module_ &m) {
  py::class_<OMPMasterTaskLoopDirective, OMPLoopDirective>(m, "OMPMasterTaskLoopDirective")
    .def("__hash__", [](const OMPMasterTaskLoopDirective& stmt) { return (intptr_t)stmt.RawStmt(); })
    .def("__eq__", [](const OMPMasterTaskLoopDirective& a, const OMPMasterTaskLoopDirective& b) { return a.RawStmt() == b.RawStmt(); })
    .def_property_readonly("has_cancel", &OMPMasterTaskLoopDirective::HasCancel);
}
} // namespace pasta
