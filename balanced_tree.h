//
// Created by Zvonimir Medic on 28/12/2016.
//

#ifndef BIOINF_VERYGOODTREE_H
#define BIOINF_VERYGOODTREE_H

#include "wavelet.h"
#include "balanced_node.h"
#include "tree.h"

#include <vector>

class very_good_tree : public tree{
 private:
  // rank kolko ih ima prije i-tog
  // select koji znak je i-ti
 public:
  very_good_tree(std::vector<zmedi_node> &nodes);
  const uint32_t rank(char i, uint32_t uint32) override;
  const uint32_t select(char i, uint32_t uint32) override;
};

#endif //BIOINF_VERYGOODTREE_H
