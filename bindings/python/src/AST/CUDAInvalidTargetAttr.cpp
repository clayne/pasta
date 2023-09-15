/*
 * Copyright (c) 2023 Trail of Bits, Inc.
 */

// This file is auto-generated.

#include <pasta/AST/AST.h>
#include <pasta/AST/Attr.h>
#include <pasta/AST/Decl.h>
#include <pasta/AST/Stmt.h>
#include <pasta/AST/Type.h>

#include "../Bindings.h"

namespace pasta {
namespace nb = nanobind;

void RegisterCUDAInvalidTargetAttr(nb::module_ &m) {
  nb::class_<CUDAInvalidTargetAttr, InheritableAttr>(m, "CUDAInvalidTargetAttr")
    .def("__hash__", [](const CUDAInvalidTargetAttr &attr) { return (intptr_t)attr.RawAttr(); })
    .def("__eq__", [](const Attr &a, const Attr &b) { return a.RawAttr() == b.RawAttr(); })
    .def_prop_ro("spelling", &CUDAInvalidTargetAttr::Spelling);
}
} // namespace pasta
