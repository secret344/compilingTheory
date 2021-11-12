cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(lexical LANGUAGES C)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")

add_executable(lexical main.c)

add_subdirectory(nfaAnalyzer)
add_subdirectory(datastructure)
add_subdirectory(readfile)

set_target_properties(lexical PROPERTIES LINK_FLAGS "-s EXIT_RUNTIME=1 -s NO_EXIT_RUNTIME=1 -s MODULARIZE=1 -s EXPORTED_FUNCTIONS=['_main','_regParse','_matchStr'] -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap','stackSave']")


target_link_libraries(lexical
  PRIVATE
  nfaAnalyzer
  datastructure
  readfile
  )