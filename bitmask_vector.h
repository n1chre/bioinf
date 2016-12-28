//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_BITMASK_VECTOR_H
#define BIOINF_BITMASK_VECTOR_H

#include <vector>
#include "bitmask.h"

class bitmask_vector : public bitmask {

 private:
  std::vector<bool> mask;

 public:

  bitmask_vector(uint32_t size);

  bitmask &set(uint32_t idx, bool b) override;
  const bool get(uint32_t idx) const override;
  const uint32_t select01(uint32_t idx, bool b) const override;
  const uint32_t rank0(uint32_t idx) const override;
  const uint32_t rank1(uint32_t idx) const override;
  const uint32_t size(void) const override;

};

#endif //BIOINF_BITMASK_VECTOR_H
