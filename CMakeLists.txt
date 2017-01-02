cmake_minimum_required(VERSION 3.6)
project(bioinf)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wall -O3")

set(SOURCE_FILES
        # bitset
        bitset.cpp bitset.h

        # bitmask
        bitmask.cpp bitmask.h
        bitmask_vector.cpp bitmask_vector.h
        bitmask_bitset.cpp bitmask_bitset.h

        # wavelet
        wavelet.cpp wavelet.h

        # lookup tree
        rank_select.h

        # rb tree
        rb_node.cpp rb_node.h
        rb_tree.cpp rb_tree.h

        # balanced tree
        lookup_list.cpp lookup_list.h

        # data
        data.cpp data.h
        )

add_executable(bioinf main.cpp ${SOURCE_FILES})
add_executable(bioinf_test test.cpp test.h ${SOURCE_FILES})