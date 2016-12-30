//
// Created by Zvonimir Medic on 28/12/2016.
//

#ifndef BIOINF_VERYGOODTREE_H
#define BIOINF_VERYGOODTREE_H

#include "wavelet.h"
#include "data.h"
#include "tree.h"

#include <algorithm>
#include <vector>

class balanced_tree : public tree {
 private:
  uint32_t size;
  std::vector<data *> nodes;
 public:
  balanced_tree(std::vector<data *> &nodes);
  const uint32_t rank(char i, uint32_t idx) const override;
  const uint32_t select(char i, uint32_t idx) const override;
};

#endif //BIOINF_VERYGOODTREE_H
