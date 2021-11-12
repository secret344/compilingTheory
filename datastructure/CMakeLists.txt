add_library(datastructure "")

file(GLOB DST_FILES_C    
    "*.c"
)

target_sources(datastructure
  PRIVATE
      ${DST_FILES_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/trie.h
      ${CMAKE_CURRENT_LIST_DIR}/stack.h
      ${CMAKE_CURRENT_LIST_DIR}/bool.h
  )
  
target_include_directories(datastructure
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )