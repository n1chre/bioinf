//
// Created by Filip Hrenic on 28/12/2016.
//

#include "bitmask_bitset.h"

bitmask_bitset::bitmask_bitset(uint32_t size) {
  mask = new bitset(size);
}

bitmask *bitmask_bitset::create(uint32_t size) {
  return new bitmask_bitset(size);
}

bitmask &bitmask_bitset::set(uint32_t idx, bool b) {
  mask->set(idx, b);
  return *this;
}

const bool bitmask_bitset::get(uint32_t idx) const {
  return (*mask)[idx];
}

const uint32_t bitmask_bitset::select01(uint32_t idx, bool b) const {
  return mask->binary_select(idx, b);
}

const uint32_t bitmask_bitset::rank0(uint32_t idx) const {
  return idx + 1 - rank1(idx);
}

const uint32_t bitmask_bitset::rank1(uint32_t idx) const {
  return mask->binary_rank(idx);
}

const uint32_t bitmask_bitset::size(void) const {
  return mask->size();
}

