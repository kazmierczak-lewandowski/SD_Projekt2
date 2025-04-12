add_library(StructuresLib INTERFACE)

target_include_directories(StructuresLib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Structures
        main.cpp
)
target_include_directories(Structures
        PRIVATE
        StructuresLib
)