#
# Copyright (c) 2023, Trail of Bits, Inc.
# 
# This source code is licensed in accordance with the terms specified in
# the LICENSE file found in the root directory of this source tree.
#

from lift import *

def run_on_ast(ast: AST, ns_name: str):
  schemas: List[Schema] = []
  lifter = SchemaLifter()

  # Filter out all tag decls that aren't private `*Impl` classes, and also
  # only look at the definitions.
  for ns in find_namespaces(ast.translation_unit, ns_name):
    for decl in decls_in_dc_decl(ns):
      if isinstance(decl, UsingShadowDecl):
        decl = decl.target_declaration

      schema: Optional[Schema] = None
      if isinstance(decl, TypeAliasDecl):
        schema = lifter.lift_type(decl.underlying_type)

      elif isinstance(decl, TagDecl):
        if decl.is_this_declaration_a_definition:
          schema: Schema = lifter.lift_decl(decl)

      if schema and isinstance(schema, NamedSchema):
        schemas.append(schema)

  for schema in schemas:
    schema.dump("")
    print()


if __name__ == "__main__":
  parser = ArgumentParser(description='Create an inventory of the API surface area of the classes / enumerator within a namespace')
  parser.add_argument('--namespace', default="to_lift")
  parser.add_argument('--local_include_dir', required=True)
  parser.add_argument('--system_include_dir', required=True)
  parser.add_argument('--working_dir', default=os.path.dirname(__file__))
  parser.add_argument('--source_file', default="Clang.cpp")
  args = parser.parse_args()
  fs: FileSystem = FileSystem.create_native()
  fm: FileManager = FileManager(fs)
  cxx: Compiler = Compiler.create_host_compiler(fm, TargetLanguage.CXX)
  argv = ArgumentVector([
      str(cxx.executable_path),
      "-x", "c++",
      "-std=c++20",
      "-isystem", str(args.local_include_dir),
      "-isystem", str(args.system_include_dir),
      str(args.source_file)])

  cmd = CompileCommand.create_from_arguments(argv, args.working_dir)
  maybe_jobs = cxx.create_jobs_for_command(cmd)
  
  if isinstance(maybe_jobs, str):
    print(maybe_jobs)
    sys.exit(1)

  for job in maybe_jobs:
    maybe_ast = job.run()
    if isinstance(maybe_ast, str):
      print(maybe_ast)
      sys.exit(1)

    elif isinstance(maybe_ast, AST):
      run_on_ast(maybe_ast, args.namespace)
