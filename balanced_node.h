//
// Created by Zvonimir Medic on 28/12/2016.
//

#ifndef BIOINF_ZMEDI_NODE_H
#define BIOINF_ZMEDI_NODE_H

#include "wavelet.h"

#include <unordered_map>
#include <utility>
#include <numeric>

class balanced_node {
 private:
  std::unordered_map<char, uint32_t> counters;
  wavelet *wave;
  uint32_t starting_idx;
  uint32_t ending_idx;
 public:
  balanced_node(std::unordered_map<char, uint32_t> counters, wavelet *wave);
  const uint32_t get_count(char c);
  const wavelet *get_wave();
};

#endif //BIOINF_ZMEDI_NODE_H
