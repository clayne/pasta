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

void RegisterBlockPointerType(nb::module_ &m) {
  nb::class_<BlockPointerType, Type>(m, "BlockPointerType")
    .def("__hash__", [](const BlockPointerType &type) { return (intptr_t)type.RawType(); })
    .def("__eq__", [](const Type &a, const Type &b) { return a.RawType() == b.RawType(); })
    .def_prop_ro("desugar", &BlockPointerType::Desugar)
    .def_prop_ro("pointee_type", &BlockPointerType::PointeeType)
    .def_prop_ro("is_sugared", &BlockPointerType::IsSugared);
}
} // namespace pasta
