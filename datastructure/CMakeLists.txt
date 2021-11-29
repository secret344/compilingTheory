add_library(datastructure "")

file(GLOB DST_FILES_C    
    "*.c"
)

target_sources(datastructure
  PRIVATE
      ${DST_FILES_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/trie.h
      ${CMAKE_CURRENT_LIST_DIR}/lex_stack.h
      ${CMAKE_CURRENT_LIST_DIR}/bool.h
      ${CMAKE_CURRENT_LIST_DIR}/cJSON.h 
      ${CMAKE_CURRENT_LIST_DIR}/memory_management.h
      ${CMAKE_CURRENT_LIST_DIR}/my_map.h
      ${CMAKE_CURRENT_LIST_DIR}/my_iterator.h
      ${CMAKE_CURRENT_LIST_DIR}/my_set.h
  )
  
target_link_libraries(datastructure
  PRIVATE 
  nfaAnalyzer
)
target_include_directories(datastructure
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )