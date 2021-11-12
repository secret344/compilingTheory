add_library(lexicalAnalyzer "")

file(GLOB NFA_LEXICAL_C    
    "*.c"
)

target_sources(lexicalAnalyzer
  PRIVATE
      ${NFA_LEXICAL_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/nfa_Intepretor.h
      ${CMAKE_CURRENT_LIST_DIR}/lexical.h
  )
  
target_include_directories(lexicalAnalyzer
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )