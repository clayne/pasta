/*
 * Copyright (c) 2021, Trail of Bits, Inc.
 *
 * This source code is licensed in accordance with the terms specified in
 * the LICENSE file found in the root directory of this source tree.
 */

#ifndef PASTA_BEGIN_CLANG_WRAPPER
# define PASTA_BEGIN_CLANG_WRAPPER(name, id)
#endif

#ifndef PASTA_END_CLANG_WRAPPER
# define PASTA_END_CLANG_WRAPPER(name, id)
#endif

#ifndef PASTA_BEGIN_BASE_CLASSES
# define PASTA_BEGIN_BASE_CLASSES(name, id)
#endif

#ifndef PASTA_END_BASE_CLASSES
# define PASTA_END_BASE_CLASSES(name, id)
#endif

#ifndef PASTA_PUBLIC_BASE_CLASS
# define PASTA_PUBLIC_BASE_CLASS(name, id, base_name, base_id)
#endif

#ifndef PASTA_BEGIN_METHODS
# define PASTA_BEGIN_METHODS(name, id)
#endif

#ifndef PASTA_END_METHODS
# define PASTA_END_METHODS(name, id)
#endif

#ifndef PASTA_CLASS_METHOD_0
# define PASTA_CLASS_METHOD_0(class_name, class_id, meth_id, method_name, rt)
#endif

#ifndef PASTA_CLASS_METHOD_1
# define PASTA_CLASS_METHOD_1(class_name, class_id, meth_id, method_name, rt, p0)
#endif

#ifndef PASTA_CLASS_METHOD_2
# define PASTA_CLASS_METHOD_2(class_name, class_id, meth_id, method_name, rt, p0, p1)
#endif

#ifndef PASTA_CLASS_METHOD_3
# define PASTA_CLASS_METHOD_3(class_name, class_id, meth_id, method_name, rt, p0, p1, p2)
#endif

#ifndef PASTA_CLASS_METHOD_4
# define PASTA_CLASS_METHOD_4(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3)
#endif

#ifndef PASTA_CLASS_METHOD_5
# define PASTA_CLASS_METHOD_5(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3, p4)
#endif

#ifndef PASTA_CLASS_METHOD_6
# define PASTA_CLASS_METHOD_6(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3, p4, p5)
#endif

#ifndef PASTA_INSTANCE_METHOD_0
# define PASTA_INSTANCE_METHOD_0(class_name, class_id, meth_id, method_name, rt)
#endif

#ifndef PASTA_INSTANCE_METHOD_1
# define PASTA_INSTANCE_METHOD_1(class_name, class_id, meth_id, method_name, rt, p0)
#endif

#ifndef PASTA_INSTANCE_METHOD_2
# define PASTA_INSTANCE_METHOD_2(class_name, class_id, meth_id, method_name, rt, p0, p1)
#endif

#ifndef PASTA_INSTANCE_METHOD_3
# define PASTA_INSTANCE_METHOD_3(class_name, class_id, meth_id, method_name, rt, p0, p1, p2)
#endif

#ifndef PASTA_INSTANCE_METHOD_4
# define PASTA_INSTANCE_METHOD_4(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3)
#endif

#ifndef PASTA_INSTANCE_METHOD_5
# define PASTA_INSTANCE_METHOD_5(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3, p4)
#endif

#ifndef PASTA_INSTANCE_METHOD_6
# define PASTA_INSTANCE_METHOD_6(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3, p4, p5)
#endif

#ifndef PASTA_OVERRIDE_METHOD_0
# define PASTA_OVERRIDE_METHOD_0(class_name, class_id, meth_id, method_name, rt)
#endif

#ifndef PASTA_OVERRIDE_METHOD_1
# define PASTA_OVERRIDE_METHOD_1(class_name, class_id, meth_id, method_name, rt, p0)
#endif

#ifndef PASTA_OVERRIDE_METHOD_2
# define PASTA_OVERRIDE_METHOD_2(class_name, class_id, meth_id, method_name, rt, p0, p1)
#endif

#ifndef PASTA_OVERRIDE_METHOD_3
# define PASTA_OVERRIDE_METHOD_3(class_name, class_id, meth_id, method_name, rt, p0, p1, p2)
#endif

#ifndef PASTA_OVERRIDE_METHOD_4
# define PASTA_OVERRIDE_METHOD_4(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3)
#endif

#ifndef PASTA_OVERRIDE_METHOD_5
# define PASTA_OVERRIDE_METHOD_5(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3, p4)
#endif

#ifndef PASTA_OVERRIDE_METHOD_6
# define PASTA_OVERRIDE_METHOD_6(class_name, class_id, meth_id, method_name, rt, p0, p1, p2, p3, p4, p5)
#endif

#ifndef PASTA_BEGIN_FIELDS
# define PASTA_BEGIN_FIELDS(name, id)
#endif

#ifndef PASTA_END_FIELDS
# define PASTA_END_FIELDS(name, id)
#endif

#ifndef PASTA_INSTANCE_FIELD
# define PASTA_INSTANCE_FIELD(class_name, class_id, field_name, field_type)
#endif

#ifndef PASTA_PRIVATE_INSTANCE_FIELD
# define PASTA_PRIVATE_INSTANCE_FIELD(class_name, class_id, field_name, field_type)
#endif

#ifndef PASTA_PROTECTED_INSTANCE_FIELD
# define PASTA_PROTECTED_INSTANCE_FIELD(class_name, class_id, field_name, field_type)
#endif

#ifndef PASTA_BEGIN_CLASS_ENUMS
# define PASTA_BEGIN_CLASS_ENUMS(class_name, class_id)
#endif

#ifndef PASTA_END_CLASS_ENUMS
# define PASTA_END_CLASS_ENUMS(class_name, class_id)
#endif

#ifndef PASTA_DECLARE_CLASS_NAMED_ENUM
# define PASTA_DECLARE_CLASS_NAMED_ENUM(class_name, class_id, enum_name, underlying_type)
#endif

#ifndef PASTA_NAMED_ENUMERATOR
# define PASTA_NAMED_ENUMERATOR(name, underlying_type, value)
#endif

#ifndef PASTA_UNNAMED_ENUMERATOR
# define PASTA_UNNAMED_ENUMERATOR(name, underlying_type, value)
#endif

#ifndef PASTA_DECLARE_NAMED_ENUM
# define PASTA_DECLARE_NAMED_ENUM(name, underlying_type)
#endif

#ifndef PASTA_BEGIN_NAMED_ENUM
# define PASTA_BEGIN_NAMED_ENUM(name, underlying_type)
#endif

#ifndef PASTA_END_NAMED_ENUM
# define PASTA_END_NAMED_ENUM(name)
#endif

#ifndef PASTA_BEGIN_CLASS_NAMED_ENUM
# define PASTA_BEGIN_CLASS_NAMED_ENUM(class_name, name, underlying_type)
#endif

#ifndef PASTA_CLASS_ENUMERATOR
# define PASTA_CLASS_ENUMERATOR(name, underlying_type, value)
#endif

#ifndef PASTA_END_CLASS_NAMED_ENUM
# define PASTA_END_CLASS_NAMED_ENUM(class_name, name)
#endif
