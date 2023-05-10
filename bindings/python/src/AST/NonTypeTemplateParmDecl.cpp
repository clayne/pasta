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

void RegisterNonTypeTemplateParmDecl(py::module_ &m) {
  py::class_<NonTypeTemplateParmDecl, DeclaratorDecl>(m, "NonTypeTemplateParmDecl")
    .def("__hash__", [](const NonTypeTemplateParmDecl& decl) { return (intptr_t)decl.RawDecl(); })
    .def("__eq__", [](const NonTypeTemplateParmDecl& a, const NonTypeTemplateParmDecl& b) { return a.RawDecl() == b.RawDecl(); })
    .def_property_readonly("default_argument_was_inherited", &NonTypeTemplateParmDecl::DefaultArgumentWasInherited)
    .def_property_readonly("default_argument", &NonTypeTemplateParmDecl::DefaultArgument)
    .def_property_readonly("default_argument_token", &NonTypeTemplateParmDecl::DefaultArgumentToken)
    .def_property_readonly("num_expansion_types", &NonTypeTemplateParmDecl::NumExpansionTypes)
    .def_property_readonly("placeholder_type_constraint", &NonTypeTemplateParmDecl::PlaceholderTypeConstraint)
    .def_property_readonly("has_default_argument", &NonTypeTemplateParmDecl::HasDefaultArgument)
    .def_property_readonly("has_placeholder_type_constraint", &NonTypeTemplateParmDecl::HasPlaceholderTypeConstraint)
    .def_property_readonly("is_expanded_parameter_pack", &NonTypeTemplateParmDecl::IsExpandedParameterPack)
    .def_property_readonly("is_pack_expansion", &NonTypeTemplateParmDecl::IsPackExpansion)
    .def_property_readonly("is_parameter_pack", &NonTypeTemplateParmDecl::IsParameterPack);
}
} // namespace pasta
