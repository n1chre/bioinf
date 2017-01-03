//
// Created by Zvonimir Medic on 28/12/2016.
//

#ifndef BIOINF_VERYGOODTREE_H
#define BIOINF_VERYGOODTREE_H

#include "wavelet.h"
#include "data.h"
#include "rank_select.h"

#include <algorithm>
#include <vector>

/**
 * Implementation of rank select that uses a sorted
 * vector of data and performs binary search on it
 */
class lookup_list : public rank_select {
 private:
  uint32_t size;
  std::vector<data *> &nodes;

 public:
  lookup_list(std::vector<data *> &nodes);
  const char operator[](const uint32_t idx) const override;
  const uint32_t rank(char i, uint32_t idx) const override;
  const uint32_t select(char i, uint32_t idx) const override;
};

#endif //BIOINF_VERYGOODTREE_H
