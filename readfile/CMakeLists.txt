add_library(readfile "")

file(GLOB READ_FILE_C    
    "*.c"
)

target_sources(readfile
  PRIVATE
      ${READ_FILE_C}
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/read_file.h     
      ${CMAKE_CURRENT_LIST_DIR}/read_str.h
  )
  
target_link_libraries(readfile
  datastructure
  )
  
target_include_directories(readfile
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )