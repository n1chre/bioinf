//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_BITSET_H
#define BIOINF_BITSET_H

#include <vector>
#include <ostream>

/**
 * Implementation of bitset that supports rank/select (implemented by popcount)
 */
class bitset {

 private:

  // popcount
  // used because it's faster than __builtin_popcount()
  static uint8_t *generate_bit_lookup(void);
  static uint8_t *BIT_LOOKUP;
  inline static uint8_t popcount(uint64_t x) {
    return BIT_LOOKUP[x >> 48] + BIT_LOOKUP[x >> 32 & 0xFFFF]
        + BIT_LOOKUP[x >> 16 & 0xFFFF] + BIT_LOOKUP[x & 0xFFFF];
  }

  std::vector<uint64_t> bits;
  uint32_t __size;
  static const std::pair<uint32_t, uint32_t> bits_position(uint32_t idx);
  static const uint8_t unit_size = sizeof(uint64_t)*8;

  inline const void check_idx(uint32_t idx) const {
    if (idx >= __size) {
      throw std::out_of_range("Index out of bounds for bitset");
    }
  }

 public:

  /**
   * Helper class used by bitset
   */
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

  /**
   * @param idx index
   * @return number of 1's before given index
   */
  uint32_t binary_rank(uint32_t idx) const;

  /**
   * @param idx index
   * @param v   value
   * @return index of idx-th occurence of v in bitset
   */
  uint32_t binary_select(uint32_t idx, bool v) const;

  /**
   * @return bitset size
   */
  const uint32_t size(void) const;

  // operators
  bool_proxy &operator[](const uint32_t idx);
  const bool_proxy operator[](const uint32_t idx) const;
  bitset &set(const uint32_t idx, bool v);

};

#endif //BIOINF_BITSET_H
