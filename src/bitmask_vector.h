//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_BITMASK_VECTOR_H
#define BIOINF_BITMASK_VECTOR_H

#include <vector>
#include <algorithm>
#include "bitmask.h"

/**
 * Implementation of bitmask which uses vector of bools
 * Because of that, operations require ~ linear time
 */
class bitmask_vector : public bitmask {

 private:
  std::vector<bool> mask;
  bitmask_vector(uint32_t size);

  inline const void check_idx(uint32_t idx) const {
    if (idx >= mask.size()) {
      throw std::out_of_range("Index out of bounds for bitmask");
    }
  }

 public:

  static bitmask *create(uint32_t size);

  bitmask &set(uint32_t idx, bool b) override;
  const bool get(uint32_t idx) const override;
  const uint32_t select01(uint32_t idx, bool b) const override;
  const uint32_t rank0(uint32_t idx) const override;
  const uint32_t rank1(uint32_t idx) const override;
  const uint32_t size(void) const override;

};

#endif //BIOINF_BITMASK_VECTOR_H
