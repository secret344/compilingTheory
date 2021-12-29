add_library(pdacompiler "")

file(GLOB READ_FILE_C    
    "*.c"
)

target_sources(pdacompiler
  PRIVATE
      ${READ_FILE_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/pda_parse.h
      ${CMAKE_CURRENT_LIST_DIR}/Lexer.h
  )

target_link_libraries(pdacompiler
  PUBLIC 
  datastructure
  dfaAnalyzer
  readfile
)


target_include_directories(pdacompiler
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )