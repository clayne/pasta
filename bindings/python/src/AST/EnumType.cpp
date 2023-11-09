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

void RegisterEnumType(nb::module_ &m) {
  nb::class_<EnumType, TagType>(m, "EnumType")
    .def("__hash__", [](const EnumType &type) { return reinterpret_cast<intptr_t>(type.RawType()); })
    .def("__eq__", [](const Type &a, const Type &b) { return a.RawType() == b.RawType(); })
    .def_prop_ro("desugar", &EnumType::Desugar)
    .def_prop_ro("declaration", &EnumType::Declaration)
    .def_prop_ro("is_sugared", &EnumType::IsSugared);
}
} // namespace pasta