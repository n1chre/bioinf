//
// Created by Filip Hrenic on 28/12/2016.
//

#include "bitmask.h"

std::function<bitmask *(uint32_t)> bitmask::CREATOR = nullptr;//&bitmask_bitset::create;

void bitmask::set_creator(std::function<bitmask *(uint32_t)> creator) {
  CREATOR = creator;
}

bitmask *bitmask::create(uint32_t size) {
  return CREATOR(size);
}
