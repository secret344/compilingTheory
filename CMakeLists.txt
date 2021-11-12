cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(lexical LANGUAGES C)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")

add_executable(lexical main.c)

add_subdirectory(lexicalAnalyzer)
add_subdirectory(datastructure)
add_subdirectory(readfile)

set_target_properties(lexical PROPERTIES LINK_FLAGS "-s EXIT_RUNTIME=1 -s MODULARIZE=1 -s EXPORTED_FUNCTIONS=['_main','_regParse','_matchStr']")


target_link_libraries(lexical
  PRIVATE
  lexicalAnalyzer
  datastructure
  readfile
  )