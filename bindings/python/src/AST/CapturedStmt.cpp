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

void RegisterCapturedStmt(nb::module_ &m) {
  nb::class_<CapturedStmt, Stmt>(m, "CapturedStmt")
    .def_prop_ro("children", &CapturedStmt::Children)
    .def_prop_ro("begin_token", &CapturedStmt::BeginToken)
    .def_prop_ro("captured_declaration", &CapturedStmt::CapturedDeclaration)
    .def_prop_ro("captured_record_declaration", &CapturedStmt::CapturedRecordDeclaration)
    .def_prop_ro("captured_region_kind", &CapturedStmt::CapturedRegionKind)
    .def_prop_ro("captured_statement", &CapturedStmt::CapturedStatement)
    .def_prop_ro("end_token", &CapturedStmt::EndToken)
    .def_prop_ro("tokens", &CapturedStmt::Tokens);
}
} // namespace pasta
