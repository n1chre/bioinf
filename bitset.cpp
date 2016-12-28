
//
// Created by Filip Hrenic on 28/12/2016.
//

#include "bitset.h"

const std::pair<uint32_t, uint32_t> bitset::bits_position(uint32_t idx) const {
  uint32_t u = sizeof(uint64_t) * 8;
  return {idx / u, idx % u};
}

bitset::bitset(uint32_t _size, uint64_t _val = 0ull) : size(_size) {
  uint32_t u = sizeof(uint64_t) * 8;
  uint32_t size = _size / u + (_size % u ? 1 : 0);

  bits.assign(size, 0ULL);
  bits[0] = _val;
}

bitset::bitset(const bitset &bs) {
  this->size = bs.size;
  this->bits = bs.bits;
}

uint32_t bitset::popcount(uint32_t idx) const {
  return 0;
}

bitset bitset::operator>>(uint32_t pos) const {
  // TODO zmedi
  return bitset(11, 11);
}

bitset::bool_proxy &bitset::operator[](const uint32_t idx) {
  auto pos = bits_position(idx);
  auto ret = new bool_proxy(this->bits.at(pos.first), pos.second);
  return *ret;
}

const bitset::bool_proxy bitset::operator[](const uint32_t idx) const {
  auto pos = bits_position(idx);
  uint64_t tmp = this->bits.at(pos.first);
  return bool_proxy(tmp, pos.second);
}

bitset &bitset::set(const uint32_t idx, bool v) {
  (*this)[idx] = v;

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

bitset::bool_proxy::bool_proxy(uint64_t &mask, uint32_t bit) : mask(mask), index(bit) {

}
bitset::bool_proxy::operator bool() const {
  return mask & (1LLU << index);
}
bitset::bool_proxy &bitset::bool_proxy::operator=(bool bit) {
  mask |= 1LLU << index;
  if (!bit) {
    mask ^= 1LLU << index;
  }
  return *this;
}
