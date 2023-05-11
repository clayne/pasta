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

void RegisterOMPParallelMaskedTaskLoopSimdDirective(py::module_ &m) {
  py::class_<OMPParallelMaskedTaskLoopSimdDirective, OMPLoopDirective>(m, "OMPParallelMaskedTaskLoopSimdDirective")
    .def("__hash__", [](const OMPParallelMaskedTaskLoopSimdDirective& stmt) { return (intptr_t)stmt.RawStmt(); })
    .def("__eq__", [](const Stmt& a, const Stmt& b) { return a.RawStmt() == b.RawStmt(); });
}
} // namespace pasta
