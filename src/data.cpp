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
  this->counters = std::unordered_map<char, uint32_t>(counters);
}

wavelet *data::get_wave() const {
  return wave;
}

uint32_t data::get_starting_idx() const {
  return starting_idx;
}

const uint32_t data::get_count(char c) const {
  try {
    uint32_t ret = this->counters.at(c);
    return ret;
  } catch (...) {
    return 0U;
  }
}

data *data::create(std::string &line, uint32_t word_size, std::unordered_map<char, uint32_t>& counters) {
  static std::string alphabet = "ACTG";

  uint32_t len = std::min(word_size, (uint32_t) line.length());
  std::string chunk = line.substr(0, len);

  std::transform(chunk.begin(), chunk.end(), chunk.begin(), ::toupper);

  line = line.substr(len);

  wavelet *_wavelet = new wavelet(chunk);
  data *_data = new data(counters, _wavelet);

  for (char c : chunk) {
    counters[c] = counters[c] + 1;
  }

  return _data;

}
