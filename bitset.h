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

 public:
  bitset(uint32_t _size, uint64_t _val);
  bitset(const bitset &bs);

  bitset operator>>(uint32_t pos) const;
  bool &operator[](const uint32_t idx);
  const bool &operator[](const uint32_t idx) const;
  bitset &set(const uint32_t idx, bool v);

  friend bitset operator&(const uint32_t lhs, const bitset &rhs);
  friend bitset operator&(const bitset &lhs, const uint32_t rhs);
  friend bitset operator&(const bitset &lhs, const bitset &rhs);

};

#endif //BIOINF_BITSET_H
