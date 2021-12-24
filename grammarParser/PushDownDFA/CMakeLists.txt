add_library(pushdowndfa "")

file(GLOB READ_FILE_C    
    "*.c"
)

target_sources(pushdowndfa
  PRIVATE
      ${READ_FILE_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/push_down_DFA.h
  )

target_link_libraries(pushdowndfa
  PUBLIC 
  datastructure
  dfaAnalyzer
  readfile
)


target_include_directories(pushdowndfa
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )