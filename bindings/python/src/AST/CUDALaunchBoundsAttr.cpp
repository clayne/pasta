/*
 * Copyright (c) 2023, Trail of Bits, Inc.
 *
 * This source code is licensed in accordance with the terms specified in
 * the LICENSE file found in the root directory of this source tree.
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

void RegisterCUDALaunchBoundsAttr(nb::module_ &m) {
  nb::class_<CUDALaunchBoundsAttr, InheritableAttr>(m, "CUDALaunchBoundsAttr")
    .def("__hash__", [](const CUDALaunchBoundsAttr &attr) { return reinterpret_cast<intptr_t>(attr.RawAttr()); })
    .def("__eq__", [](const Attr &a, const Attr &b) { return a.RawAttr() == b.RawAttr(); })
    .def("__ne__", [](const Attr &a, const Attr &b) { return a.RawAttr() != b.RawAttr(); })
    .def_prop_ro("max_blocks", &CUDALaunchBoundsAttr::MaxBlocks)
    .def_prop_ro("max_threads", &CUDALaunchBoundsAttr::MaxThreads)
    .def_prop_ro("min_blocks", &CUDALaunchBoundsAttr::MinBlocks)
    .def_prop_ro("spelling", &CUDALaunchBoundsAttr::Spelling);
}
} // namespace pasta
