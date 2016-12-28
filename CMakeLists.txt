cmake_minimum_required(VERSION 3.6)
project(bioinf)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wall")

set(SOURCE_FILES
        main.cpp

        # bitset
        bitset.cpp bitset.h

        # bitmask
        bitmask.cpp bitmask.h
        bitmask_vector.cpp bitmask_vector.h

        # wavelet
        wavelet.cpp wavelet.h

        # lookup tree
        tree.h

        # rb tree
        RBTree.cpp RBTree.h RBNode.cpp RBNode.h

        # balanced tree
        balanced_node.cpp balanced_node.h
        balanced_tree.cpp balanced_tree.h
        )

add_executable(bioinf ${SOURCE_FILES})