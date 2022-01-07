add_library(Compilerparsetablebuild "")

file(GLOB READ_FILE_C    
    "*.c"
)

target_sources(Compilerparsetablebuild
  PRIVATE
      ${READ_FILE_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/parse_table_builder.h
  )

target_link_libraries(Compilerparsetablebuild
  PUBLIC 
  datastructure
  dfaAnalyzer
  readfile
  pdacompiler
)


target_include_directories(Compilerparsetablebuild
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )