//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_BITMASK_BITSET_H
#define BIOINF_BITMASK_BITSET_H

#include "bitmask.h"
#include "bitset.h"

class bitmask_bitset : public bitmask {

 private:
  bitset *mask;

 public:

  bitmask_bitset(uint32_t size);

  bitmask &set(uint32_t idx, bool b) override;
  const bool get(uint32_t idx) const override;
  const uint32_t select01(uint32_t idx, bool b) const override;
  const uint32_t rank0(uint32_t idx) const override;
  const uint32_t rank1(uint32_t idx) const override;
  const uint32_t size(void) const override;

};

#endif //BIOINF_BITMASK_BITSET_H
