//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_BITMASK_H
#define BIOINF_BITMASK_H

#include <cstdint>

class bitmask {

  virtual bitmask &clear(void) = 0;
  virtual const uint32_t select0(uint32_t idx) const = 0;
  virtual const uint32_t select1(uint32_t idx) const = 0;
  virtual const uint32_t rank0(uint32_t idx) const = 0;
  virtual const uint32_t rank1(uint32_t idx) const = 0;
  virtual const uint32_t size(void) const = 0;

};

#endif //BIOINF_BITMASK_H
