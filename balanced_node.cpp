//
// Created by Zvonimir Medic on 28/12/2016.
//

#include "balanced_node.h"

balanced_node::balanced_node(std::unordered_map<char, uint32_t> counters, wavelet *wave) {
  this->wave = wave;
  this->counters = counters;
  this->starting_idx = std::accumulate(std::begin(counters),
                                       std::end(counters),
                                       0U,
                                       [](const uint32_t previous, const std::pair<char, uint32_t> &p) {
                                         return previous + p.second;
                                       });
  this->ending_idx = this->starting_idx + wave->length();

}

const uint32_t balanced_node::get_count(char c) const {
  return this->counters.at(c);
}

const wavelet *balanced_node::get_wave() const {
  return this->wave;
}

const uint32_t balanced_node::get_starting_idx(void) const {
  return this->starting_idx;
}
const uint32_t balanced_node::get_ending_idx(void) const {
  return this->ending_idx;
}

