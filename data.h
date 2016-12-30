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
  const std::unordered_map<char, uint32_t> &get_counters() const;
  void set_counters(const std::unordered_map<char, uint32_t> &counters);
  wavelet *get_wave() const;
  void set_wave(wavelet *wave);
  uint32_t get_starting_idx() const;
  void set_starting_idx(uint32_t starting_idx);
  uint32_t get_ending_idx() const;
  void set_ending_idx(uint32_t ending_idx);
  const uint32_t get_count(char c) const;
};

#endif //BIOINF_DATA_H
