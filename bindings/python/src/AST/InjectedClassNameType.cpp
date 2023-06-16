/*
 * Copyright (c) 2023 Trail of Bits, Inc.
 */

// This file is auto-generated.

#include <pasta/AST/AST.h>
#include <pasta/AST/Attr.h>
#include <pasta/AST/Decl.h>
#include <pasta/AST/Stmt.h>
#include <pasta/AST/Type.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/vector.h>

namespace pasta {
namespace nb = nanobind;

void RegisterInjectedClassNameType(nb::module_ &m) {
  nb::class_<InjectedClassNameType, Type>(m, "InjectedClassNameType")
    .def("__hash__", [](const InjectedClassNameType& type) { return (intptr_t)type.RawType(); })
    .def("__eq__", [](const Type& a, const Type& b) { return a.RawType() == b.RawType(); })
    .def_prop_ro("desugar", &InjectedClassNameType::Desugar)
    .def_prop_ro("declaration", &InjectedClassNameType::Declaration)
    .def_prop_ro("injected_specialization_type", &InjectedClassNameType::InjectedSpecializationType)
    .def_prop_ro("injected_tst", &InjectedClassNameType::InjectedTST)
    .def_prop_ro("is_sugared", &InjectedClassNameType::IsSugared);
}
} // namespace pasta
