cmake_minimum_required(VERSION 3.6)
project(bioinf)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp wavelet_simple.cpp wavelet_simple.h RBTree.cpp RBTree.h RBNode.cpp RBNode.h)
add_executable(bioinf ${SOURCE_FILES})