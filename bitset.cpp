
//
// Created by Filip Hrenic on 28/12/2016.
//

#include "bitset.h"
#include <iostream>

uint8_t *bitset::generate_bit_lookup(void) {
  uint8_t *arr = new uint8_t[0xFFFF + 1];

  for (uint32_t i = 0; i <= 0xFFFF; i++) {
    uint32_t x = i;
    uint8_t count;
    for (count = 0; x; count++) {
      x &= x - 1;
    }
    arr[i] = count;
  }

  return arr;
}

uint8_t *bitset::BIT_LOOKUP = bitset::generate_bit_lookup();

uint8_t bitset::popcount(uint64_t x) {
  return BIT_LOOKUP[x >> 48] + BIT_LOOKUP[x >> 32 & 0xFFFF]
      + BIT_LOOKUP[x >> 16 & 0xFFFF] + BIT_LOOKUP[x & 0xFFFF];
}

const std::pair<uint32_t, uint32_t> bitset::bits_position(uint32_t idx) {
  return {idx/unit_size, idx%unit_size};
}

bitset::bitset(uint32_t _size, uint64_t _val) : __size(_size) {
  auto p = bits_position(_size - 1);
  uint32_t size = p.first + 1;

  bits.assign(size, 0ULL);
  if (size!=1 || _size==unit_size) {
    bits[0] = _val;
  } else {
    bits[0] = _val & ((1LLU << _size) - 1);
  }
}

bitset::bitset(const bitset &bs) {
  this->__size = bs.__size;
  this->bits = bs.bits;
}

uint32_t bitset::binary_rank(uint32_t idx) const {
  uint32_t sol = 0;
  auto pos = bits_position(idx);
  for (int i = 0; i < pos.first; ++i) {
    sol += popcount(bits[i]);
  }
  sol += popcount(bits[pos.first] & (1ull << pos.second) - 1);
  return sol;
}

uint32_t bitset::binary_select(uint32_t idx, bool v) const {
  uint32_t sum = 0;

  auto f = [=](uint64_t x) -> uint8_t { return v ? popcount(x) : unit_size - popcount(x); };

  uint32_t i = 0;
  uint32_t val;

  do {
    val = f(bits[i]);
    if (sum + val > idx) { break; }
    sum += val;
    ++i;
  } while (i < bits.size());

  if (i==bits.size()) {
    throw -1;
  }

//  std::cout << val << std::endl;

  uint32_t j;
  for (j = 0; j < unit_size; j++) {
    if (((bool) (bits[i] & (1llu << j)))==v) { sum++; }
    if (sum > idx) { break; }
  }

  if (j==unit_size) {
    throw -2;
  }

  return i*unit_size + j;
}

bitset bitset::operator>>(uint32_t pos) const {
  auto discard_data = bits_position(pos);
  uint64_t all_one_mask = (1LLU << discard_data.second) - 1;
  bitset ret = *this;
  std::vector<uint64_t> new_bits;
  for (auto i = discard_data.first; i < ret.bits.size(); ++i) {
    auto curr = ret.bits.at(i);
    uint64_t next;
    if (i + 1==ret.bits.size()) {
      next = 0LLU;
    } else {
      next = ret.bits.at(i + 1);
    }
    curr = (curr >> discard_data.second)
        | (next & all_one_mask) << (unit_size - discard_data.second);
    new_bits.emplace_back(curr);
  }
  for (auto i = 0; i < discard_data.first; ++i) {
    new_bits.emplace_back(0LLU);
  }
  ret.bits = new_bits;

  // TODO zmedi
  return ret;
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
  return lhs & bitset(lhs.__size, rhs);
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

const uint32_t bitset::size(void) const {
  return __size;
}
