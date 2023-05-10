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

void RegisterTypeAliasTemplateDecl(py::module_ &m) {
  py::class_<TypeAliasTemplateDecl, RedeclarableTemplateDecl>(m, "TypeAliasTemplateDecl")
    .def("__hash__", [](const TypeAliasTemplateDecl& decl) { return (intptr_t)decl.RawDecl(); })
    .def("__eq__", [](const TypeAliasTemplateDecl& a, const TypeAliasTemplateDecl& b) { return a.RawDecl() == b.RawDecl(); })
    .def_property_readonly("canonical_declaration", &TypeAliasTemplateDecl::CanonicalDeclaration)
    .def_property_readonly("instantiated_from_member_template", &TypeAliasTemplateDecl::InstantiatedFromMemberTemplate)
    .def_property_readonly("previous_declaration", &TypeAliasTemplateDecl::PreviousDeclaration)
    .def_property_readonly("templated_declaration", &TypeAliasTemplateDecl::TemplatedDeclaration);
}
} // namespace pasta
