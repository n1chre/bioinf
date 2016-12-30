//
// Created by Matija Orsolic on 30/12/2016.
//

#include "data.h"

data::data(const std::unordered_map<char, uint32_t> &counters, wavelet *wave) : counters(counters), wave(wave) {
  this->starting_idx = std::accumulate(std::begin(counters),
                                       std::end(counters),
                                       0U,
                                       [](const uint32_t previous, const std::pair<char, uint32_t> &p) {
                                         return previous + p.second;
                                       });
  this->ending_idx = this->starting_idx + wave->length();
}

const std::unordered_map<char, uint32_t> &data::getCounters() const {
  return counters;
}

void data::setCounters(const std::unordered_map<char, uint32_t> &counters) {
  data::counters = counters;
}

wavelet *data::getWave() const {
  return wave;
}

void data::setWave(wavelet *wave) {
  data::wave = wave;
}

uint32_t data::getStarting_idx() const {
  return starting_idx;
}

void data::setStarting_idx(uint32_t starting_idx) {
  data::starting_idx = starting_idx;
}

uint32_t data::getEnding_idx() const {
  return ending_idx;
}

void data::setEnding_idx(uint32_t ending_idx) {
  data::ending_idx = ending_idx;
}
