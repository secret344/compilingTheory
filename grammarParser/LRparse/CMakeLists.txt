add_library(lrparse "")

file(GLOB READ_FILE_C
    "*.C"
)

target_sources(lrparse
    PRIVATE
        ${READ_FILE_C}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/LRcompiler.h
)

target_link_libraries(lrparse
    PUBLIC
    datastructure
    Compilerparsetablebuild
)

target_include_directories(lrparse
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)