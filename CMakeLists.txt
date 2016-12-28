cmake_minimum_required(VERSION 3.6)
project(bioinf)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp wavelet_simple.cpp wavelet_simple.h RBTree.cpp RBTree.h RBNode.cpp RBNode.h balanced_tree.cpp balanced_tree.h wavelet.h balanced_node.cpp balanced_node.h tree.cpp tree.h)
add_executable(bioinf ${SOURCE_FILES})