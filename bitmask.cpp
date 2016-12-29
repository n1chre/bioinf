#include "bitmask.h"
//
// Created by Filip Hrenic on 28/12/2016.
//

#include "bitmask_bitset.h"

bitmask *bitmask::create(uint32_t size) {
//  return new bitmask_vector(size);
  return new bitmask_bitset(size);
}
