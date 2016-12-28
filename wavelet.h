//
// Created by Zvonimir Medic on 28/12/2016.
//
#ifndef BIOINF_ABSTRACT_NODE_H
#define BIOINF_ABSTRACT_NODE_H

#include <cstdint>

class wavelet {
 public:
  virtual const uint32_t rank(char, uint32_t) = 0;
  virtual const uint32_t select(char, uint32_t) = 0;
};

#endif //BIOINF_ABSTRACT_NODE_H
