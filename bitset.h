//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_BITSET_H
#define BIOINF_BITSET_H

#include <vector>
#include <ostream>

class bitset {

 private:
  std::vector<uint64_t> bits;
  uint32_t size;
  const std::pair<uint32_t, uint32_t> bits_position(uint32_t idx) const;
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

  bitset(uint32_t _size, uint64_t _val);
  bitset(const bitset &bs);

  uint32_t popcount(uint32_t idx) const;

  bitset operator>>(uint32_t pos) const;
  bool_proxy &operator[](const uint32_t idx);
  const bool_proxy operator[](const uint32_t idx) const;
  bitset &set(const uint32_t idx, bool v);

  friend bitset operator&(const uint32_t lhs, const bitset &rhs);
  friend bitset operator&(const bitset &lhs, const uint32_t rhs);
  friend bitset operator&(const bitset &lhs, const bitset &rhs);

};

#endif //BIOINF_BITSET_H
