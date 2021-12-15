add_library(dfaAnalyzer "")

file(GLOB READ_FILE_C    
    "*.c"
)

target_sources(dfaAnalyzer
  PRIVATE
      ${READ_FILE_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/dfa_parse.h
      ${CMAKE_CURRENT_LIST_DIR}/dfa_Intepretor.h
  )

target_link_libraries(dfaAnalyzer
  PUBLIC 
  datastructure
  nfaAnalyzer
)

target_include_directories(dfaAnalyzer
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )