#!/usr/bin/env bash

SOURCE_FILES="bitset.cpp bitset.h bitmask.cpp bitmask.h bitmask_vector.cpp bitmask_vector.h
bitmask_bitset.cpp bitmask_bitset.h wavelet.cpp wavelet.h rank_select.h rb_node.cpp rb_node.h
rb_tree.cpp rb_tree.h lookup_list.cpp lookup_list.h data.cpp data.h"

if [[ -f bioinf ]]; then
    rm -f bioinf
fi

if [[ -f bioinf-test ]]; then
    rm -f bioinf-test
fi

g++-5 -std=c++14 -Ofast -march=native -flto -frename-registers -freciprocal-math -fno-signed-zeros -fno-trapping-math -funroll-loops  -fassociative-math -o bioinf main.cpp ${SOURCE_FILES}
g++-5 -std=c++14 -Ofast -march=native -flto -frename-registers -freciprocal-math -fno-signed-zeros -fno-trapping-math -funroll-loops  -fassociative-math -o bioinf-test test.h test.cpp ${SOURCE_FILES}