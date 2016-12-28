//
// Created by Zvonimir Medic on 28/12/2016.
//

#ifndef BIOINF_TREE_H
#define BIOINF_TREE_H

#include <cstdint>

class tree {
 public:
  virtual const uint32_t rank(char, uint32_t) const = 0;
  virtual const uint32_t select(char, uint32_t) const = 0;
};

#endif //BIOINF_TREE_H
