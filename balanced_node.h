//
// Created by Zvonimir Medic on 28/12/2016.
//

#include <unordered_map>
#include "wavelet.h"

#ifndef BIOINF_ZMEDI_NODE_H
#define BIOINF_ZMEDI_NODE_H

class zmedi_node {
 private:
  std::unordered_map<char, uint32_t> counters;
  wavelet *wave;
 public:
  zmedi_node(std::unordered_map<char, uint32_t> counters, wavelet *wave);
  uint32_t getCount(char c);
  wavelet *getWave();
};

#endif //BIOINF_ZMEDI_NODE_H
