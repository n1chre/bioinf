//
// Created by Matija Orsolic on 30/12/2016.
//

#ifndef BIOINF_DATA_H
#define BIOINF_DATA_H

#include <utility>
#include <unordered_map>
#include <numeric>

#include "wavelet.h"

class data {
 private:
  std::unordered_map<char, uint32_t> counters;
  wavelet *wave;
  uint32_t starting_idx;
  uint32_t ending_idx;
 public:
  data(const std::unordered_map<char, uint32_t> &counters, wavelet *wave);
  const std::unordered_map<char, uint32_t> &getCounters() const;
  void setCounters(const std::unordered_map<char, uint32_t> &counters);
  wavelet *getWave() const;
  void setWave(wavelet *wave);
  uint32_t getStarting_idx() const;
  void setStarting_idx(uint32_t starting_idx);
  uint32_t getEnding_idx() const;
  void setEnding_idx(uint32_t ending_idx);
};

#endif //BIOINF_DATA_H
