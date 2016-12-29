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
        bitmask_bitset.cpp bitmask_bitset.h

        # wavelet
        wavelet.cpp wavelet.h

        # lookup tree
        tree.h

        # rb tree
        rb_node.cpp rb_node.h
        rb_tree.cpp rb_tree.h

        #balanced tree
        balanced_node.cpp balanced_node.h
        balanced_tree.cpp balanced_tree.h

        )

add_executable(bioinf ${SOURCE_FILES})