cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(lexical LANGUAGES C)

add_executable(lexical main.c)

add_subdirectory(lexicalAnalyzer)
add_subdirectory(datastructure)
add_subdirectory(readfile)

target_link_libraries(lexical
  PRIVATE
  lexicalAnalyzer
  datastructure
  readfile
  )