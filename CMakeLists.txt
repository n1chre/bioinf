cmake_minimum_required(VERSION 3.6)
project(bioinf)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wall -O3")

set(SOURCE_FILES
        # bitset
        src/bitset.cpp src/bitset.h

        # bitmask
        src/bitmask.cpp src/bitmask.h
        src/bitmask_vector.cpp src/bitmask_vector.h
        src/bitmask_bitset.cpp src/bitmask_bitset.h

        # wavelet
        src/wavelet.cpp src/wavelet.h

        # lookup tree
        src/rank_select.h

        # rb tree
        src/rb_node.cpp src/rb_node.h
        src/rb_tree.cpp src/rb_tree.h

        # balanced tree
        src/lookup_list.cpp src/lookup_list.h

        # data
        src/data.cpp src/data.h
        )

add_executable(bioinf src/main.cpp ${SOURCE_FILES})
add_executable(bioinf_test src/test.cpp src/test.h ${SOURCE_FILES})