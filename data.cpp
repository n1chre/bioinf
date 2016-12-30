//
// Created by Matija Orsolic on 30/12/2016.
//

#include "data.h"

//#include <iostream>

data::data(const std::unordered_map<char, uint32_t> &counters, wavelet *wave) : counters(counters), wave(wave) {
  this->starting_idx = std::accumulate(std::begin(counters),
                                       std::end(counters),
                                       0U,
                                       [](const uint32_t previous, const std::pair<char, uint32_t> &p) {
                                         return previous + p.second;
                                       });
  this->ending_idx = this->starting_idx + wave->length();
  this->counters = std::unordered_map<char, uint32_t>(counters);
  //std::cerr << "Imam idx: " << starting_idx << std::endl;
}

const std::unordered_map<char, uint32_t> &data::get_counters() const {
  return counters;
}

void data::set_counters(const std::unordered_map<char, uint32_t> &counters) {
  data::counters = counters;
}

wavelet *data::get_wave() const {
  return wave;
}

void data::set_wave(wavelet *wave) {
  data::wave = wave;
}

uint32_t data::get_starting_idx() const {
  return starting_idx;
}

void data::set_starting_idx(uint32_t starting_idx) {
  data::starting_idx = starting_idx;
}

uint32_t data::get_ending_idx() const {
  return ending_idx;
}

void data::set_ending_idx(uint32_t ending_idx) {
  data::ending_idx = ending_idx;
}

const uint32_t data::get_count(char c) const {
  try {
    uint32_t ret = this->counters.at(c);
    return ret;
  } catch (...) {
    return 0U;
  }
}
