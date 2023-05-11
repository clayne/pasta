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

void RegisterFriendTemplateDecl(py::module_ &m) {
  py::class_<FriendTemplateDecl, Decl>(m, "FriendTemplateDecl")
    .def("__hash__", [](const FriendTemplateDecl& decl) { return (intptr_t)decl.RawDecl(); })
    .def("__eq__", [](const Decl& a, const Decl& b) { return a.RawDecl() == b.RawDecl(); })
    .def_property_readonly("friend_declaration", &FriendTemplateDecl::FriendDeclaration)
    .def_property_readonly("friend_token", &FriendTemplateDecl::FriendToken)
    .def_property_readonly("friend_type", &FriendTemplateDecl::FriendType)
    .def_property_readonly("num_template_parameters", &FriendTemplateDecl::NumTemplateParameters);
}
} // namespace pasta
