//
// Created by Matija Orsolic on 30/12/2016.
//

#ifndef BIOINF_DATA_H
#define BIOINF_DATA_H

#include <utility>
#include <unordered_map>
#include <numeric>

#include "wavelet.h"

/**
 * Represents data used to answer rank/select queries.
 * Has meta data for lookup
 */
class data {
 private:
  std::unordered_map<char, uint32_t> counters;
  wavelet *wave;
  uint32_t starting_idx;

 public:
  data(const std::unordered_map<char, uint32_t> &counters, wavelet *wave);
  wavelet *get_wave() const;
  uint32_t get_starting_idx() const;
  const uint32_t get_count(char c) const;
};

#endif //BIOINF_DATA_H
