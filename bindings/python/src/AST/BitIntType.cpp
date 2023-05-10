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

void RegisterBitIntType(py::module_ &m) {
  py::class_<BitIntType, Type>(m, "BitIntType")
    .def("__hash__", [](const BitIntType& type) { return (intptr_t)type.RawType(); })
    .def("__eq__", [](const BitIntType& a, const BitIntType& b) { return a.RawType() == b.RawType(); })
    .def_property_readonly("desugar", &BitIntType::Desugar)
    .def_property_readonly("num_bits", &BitIntType::NumBits)
    .def_property_readonly("is_signed", &BitIntType::IsSigned)
    .def_property_readonly("is_sugared", &BitIntType::IsSugared)
    .def_property_readonly("is_unsigned", &BitIntType::IsUnsigned);
}
} // namespace pasta
