//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_BITSET_H
#define BIOINF_BITSET_H

#include <vector>
#include <ostream>

class bitset {


 private:

  // popcount
  static uint8_t *generate_bit_lookup(void);
  static uint8_t *BIT_LOOKUP;
  static uint8_t popcount(uint64_t x);

  std::vector<uint64_t> bits;
  uint32_t __size;
  static const std::pair<uint32_t, uint32_t> bits_position(uint32_t idx);
  static const uint8_t unit_size = sizeof(uint64_t)*8;

 public:

  class bool_proxy {
   public:
    bool_proxy(uint64_t &mask, uint32_t bit);

    operator bool() const;
    bool_proxy &operator=(bool bit);

   private:
    uint64_t &mask;
    uint32_t index;
  };

  bitset(uint32_t _size, uint64_t _val = 0LLU);
  bitset(const bitset &bs);

  uint32_t binary_rank(uint32_t idx) const;
  uint32_t binary_select(uint32_t idx, bool v) const;

  bitset operator>>(uint32_t pos) const;
  bool_proxy &operator[](const uint32_t idx);
  const bool_proxy operator[](const uint32_t idx) const;
  bitset &set(const uint32_t idx, bool v);

  const uint32_t size(void) const;

  friend bitset operator&(const uint32_t lhs, const bitset &rhs);
  friend bitset operator&(const bitset &lhs, const uint32_t rhs);
  friend bitset operator&(const bitset &lhs, const bitset &rhs);

};

#endif //BIOINF_BITSET_H
