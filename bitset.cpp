
//
// Created by Filip Hrenic on 28/12/2016.
//

#include "bitset.h"

bitset::bitset(uint32_t _size, uint64_t _val = 0ull) : size(_size) {
  uint32_t u = sizeof(uint64_t)*8;
  uint32_t size = _size/u + (_size%u ? 1 : 0);

  bits.assign(size, 0ULL);
  bits[0] = _val;
}

bitset::bitset(const bitset &bs) {
  this->size = bs.size;
  this->bits = bs.bits;
}

bitset bitset::operator>>(uint32_t pos) const {
  return bitset(0);
}

bitset operator&(const uint32_t lhs, const bitset &rhs) {
  return rhs & lhs;
}

bitset operator&(const bitset &lhs, const uint32_t rhs) {
  return lhs & bitset(lhs.size, rhs);
}

bitset operator&(const bitset &lhs, const bitset &rhs) {
  bitset ret = lhs;
  for (int i = 0; i < lhs.bits.size(); ++i) {
    ret.bits[i] &= rhs.bits[i];
  }
  return ret;
}

