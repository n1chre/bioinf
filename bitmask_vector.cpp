//
// Created by Filip Hrenic on 28/12/2016.
//

#include "bitmask_vector.h"

bitmask_vector::bitmask_vector(uint32_t size) {
  mask.assign(size, false);
}

bitmask &bitmask_vector::set(uint32_t idx, bool b) {
  mask[idx] = b;
  return *this;
}

const bool bitmask_vector::get(uint32_t idx) const {
  return mask[idx];
}

const uint32_t bitmask_vector::select01(uint32_t idx, bool b) const {
  uint32_t sol = 0;
  for (auto it = mask.begin(); it!=mask.end(); it++) {
    if (*it==b) {
      if (idx--==0) {
        return sol;
      }
    }
    sol++;
  }
  throw -1;
}

const uint32_t bitmask_vector::rank0(uint32_t idx) const {
  auto it = mask.begin();
  return (uint32_t) std::count(it, it + idx, false);
}

const uint32_t bitmask_vector::rank1(uint32_t idx) const {
  return idx - rank0(idx);
}

const uint32_t bitmask_vector::size(void) const {
  return (uint32_t) mask.size();
}
