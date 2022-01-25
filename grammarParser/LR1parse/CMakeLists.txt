add_library(lr1parse "")

file(GLOB READ_FILE_C
    "*.C"
)

target_sources(lr1parse
    PRIVATE
        ${READ_FILE_C}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/LR1compiler.h
)

target_link_libraries(lr1parse
    PUBLIC
    datastructure
    Compilerparsetablebuild
)

target_include_directories(lr1parse
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)