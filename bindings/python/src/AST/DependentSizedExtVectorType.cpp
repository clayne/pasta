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

void RegisterDependentSizedExtVectorType(nb::module_ &m) {
  nb::class_<DependentSizedExtVectorType, Type>(m, "DependentSizedExtVectorType")
    .def_prop_ro("desugar", &DependentSizedExtVectorType::Desugar)
    .def_prop_ro("attribute_token", &DependentSizedExtVectorType::AttributeToken)
    .def_prop_ro("element_type", &DependentSizedExtVectorType::ElementType)
    .def_prop_ro("size_expression", &DependentSizedExtVectorType::SizeExpression)
    .def_prop_ro("is_sugared", &DependentSizedExtVectorType::IsSugared);
}
} // namespace pasta
