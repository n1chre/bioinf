//
// Created by Filip Hrenic on 28/12/2016.
//

#include "bitmask_bitset.h"

bitmask_bitset::bitmask_bitset(uint32_t size) {
//  mask = new bitset(size);
}

bitmask &bitmask_bitset::set(uint32_t idx, bool b) {
  mask->set(idx, b);
  return *this;
}

const bool bitmask_bitset::get(uint32_t idx) const {
  return (*mask)[idx];
}

const uint32_t bitmask_bitset::select01(uint32_t idx, bool b) const {
//  uint32_t _idx = mask->select(idx);
//  if (!b) { _idx = idx - _idx; }
}

const uint32_t bitmask_bitset::rank0(uint32_t idx) const {
  return idx - rank1(idx);
}

const uint32_t bitmask_bitset::rank1(uint32_t idx) const {
  return mask->popcount(idx);
}

const uint32_t bitmask_bitset::size(void) const {
//  return mask->size();
}

