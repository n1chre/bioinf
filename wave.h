//
// Created by Zvonimir Medic on 28/12/2016.
//
#include <cstdint>
#ifndef BIOINF_ABSTRACT_NODE_H
#define BIOINF_ABSTRACT_NODE_H

class wave {
 public:
  virtual const uint32_t rank(char, uint32_t) = 0;
  virtual const uint32_t select(char, uint32_t) = 0;
};

#endif //BIOINF_ABSTRACT_NODE_H
