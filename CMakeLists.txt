cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(lexical LANGUAGES C)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")

add_executable(lexical main.c)

add_subdirectory(nfaAnalyzer)
add_subdirectory(dfaAnalyzer)
add_subdirectory(datastructure)
add_subdirectory(readfile)

set_target_properties(lexical PROPERTIES LINK_FLAGS "-gsource-map --source-map-base  -fsanitize=address -s ALLOW_MEMORY_GROWTH -s EXIT_RUNTIME=1 -s NO_EXIT_RUNTIME=1 -s MODULARIZE=1 -s EXPORTED_FUNCTIONS=['_main','_regParse','_matchStr','_dfaParse'] -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap','stackSave','getValue']")


target_link_libraries(lexical
  PRIVATE
  nfaAnalyzer
  dfaAnalyzer
  )