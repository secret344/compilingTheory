add_library(LRparse "")

file(GLOB READ_FILE_C
    "*.C"
)

target_sources(LRparse
    PRIVATE
        ${READ_FILE_C}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/LRcompiler.h
)

target_link_libraries(LRparse
    PUBLIC
    datastructure
    Compilerparsetablebuild
)

target_include_directories(LRparse
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)