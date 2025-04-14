add_library(StructuresLib STATIC
        Heap.cpp
        Heap.hpp
        BinarySearchTree.cpp
        BinarySearchTree.hpp
        Collection.cpp
        Collection.hpp
        Utils.cpp
        Utils.hpp
        Element.hpp
)
target_include_directories(StructuresLib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Structures
        main.cpp
)
target_include_directories(Structures
        PRIVATE
        StructuresLib
)
target_link_libraries(Structures
        PRIVATE
        StructuresLib
)