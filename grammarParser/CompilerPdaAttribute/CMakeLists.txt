add_library(compilerPdaAttribute "")

file(GLOB READ_FILE_C    
    "*.c"
)

target_sources(compilerPdaAttribute
  PRIVATE
      ${READ_FILE_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/parse_table_builder.h
  )

target_link_libraries(compilerPdaAttribute
  PUBLIC 
  datastructure
  dfaAnalyzer
  readfile
  pdacompiler
)


target_include_directories(compilerPdaAttribute
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )