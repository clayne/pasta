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

void RegisterOMPForDirective(nb::module_ &m) {
  nb::class_<OMPForDirective, OMPLoopDirective>(m, "OMPForDirective")
    .def_prop_ro("task_reduction_reference_expression", &OMPForDirective::TaskReductionReferenceExpression)
    .def_prop_ro("has_cancel", &OMPForDirective::HasCancel);
}
} // namespace pasta
