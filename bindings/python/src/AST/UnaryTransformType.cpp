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

void RegisterUnaryTransformType(py::module_ &m) {
  py::class_<UnaryTransformType, Type>(m, "UnaryTransformType")
    .def("__hash__", [](const UnaryTransformType& type) { return (intptr_t)type.RawType(); })
    .def("__eq__", [](const Type& a, const Type& b) { return a.RawType() == b.RawType(); })
    .def_property_readonly("desugar", &UnaryTransformType::Desugar)
    .def_property_readonly("base_type", &UnaryTransformType::BaseType)
    .def_property_readonly("utt_kind", &UnaryTransformType::UTTKind)
    .def_property_readonly("underlying_type", &UnaryTransformType::UnderlyingType)
    .def_property_readonly("is_sugared", &UnaryTransformType::IsSugared);
}
} // namespace pasta
