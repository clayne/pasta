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
#include <pasta/AST/Printer.h>
#include <pasta/AST/Stmt.h>
#include <pasta/AST/Token.h>
#include <pasta/AST/Type.h>

#include "../Bindings.h"

namespace pasta {
namespace nb = nanobind;

void RegisterStmt(nb::module_ &m) {
  nb::class_<Stmt>(m, "Stmt")
    .def("__hash__", [](const Stmt& stmt) { return reinterpret_cast<intptr_t>(stmt.RawStmt()); })
    .def("__eq__", [](const Stmt& a, const Stmt& b) { return a.RawStmt() == b.RawStmt(); })
    .def("__ne__", [](const Stmt& a, const Stmt& b) { return a.RawStmt() != b.RawStmt(); })
    .def_static("cast", nb::overload_cast<const TokenContext &>(&Decl::From))
    .def_prop_ro("ignore_containers", &Stmt::IgnoreContainers)
    .def_prop_ro("children", &Stmt::Children)
    .def_prop_ro("begin_token", &Stmt::BeginToken)
    .def_prop_ro("end_token", &Stmt::EndToken)
    .def_prop_ro("id", &Stmt::ID)
    .def_prop_ro("tokens", &Stmt::Tokens)
    .def_prop_ro("kind", &Stmt::Kind)
    .def_prop_ro("kind_name", &Stmt::KindName)
    .def_prop_ro("strip_label_like_statements", &Stmt::StripLabelLikeStatements);
}
} // namespace pasta
