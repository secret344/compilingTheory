add_library(nfaAnalyzer "")

file(GLOB NFA_LEXICAL_C    
    "*.c"
)

target_sources(nfaAnalyzer
  PRIVATE
      ${NFA_LEXICAL_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/nfa_Intepretor.h
      ${CMAKE_CURRENT_LIST_DIR}/nfa_parse.h
  )

target_link_libraries(nfaAnalyzer
  PUBLIC 
  readfile
  datastructure
  )

target_include_directories(nfaAnalyzer
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )