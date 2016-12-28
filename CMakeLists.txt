cmake_minimum_required(VERSION 3.6)
project(bioinf)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp wave_node_simple.cpp wave_node_simple.h RBTree.cpp RBTree.h RBNode.cpp RBNode.h very_good_tree.cpp very_good_tree.h wave.h)
add_executable(bioinf ${SOURCE_FILES})