
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
  // TODO zmedi
  return bitset(0);
}

bool &bitset::operator[](const uint32_t idx) {
  // TODO zmedi
  bool ret = false;
  return ret;
}

const bool &bitset::operator[](const uint32_t idx) const {
  // TODO zmedi
  return false;
}

bitset &bitset::set(const uint32_t idx, bool v) {
  // TODO zmedi
  return *this;
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

