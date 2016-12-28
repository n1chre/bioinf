//
// Created by Zvonimir Medic on 28/12/2016.
//

#include "balanced_node.h"

zmedi_node::zmedi_node(std::unordered_map<char, uint32_t> counters, wavelet *wave) {
  this->wave = wave;
  this->counters = counters;
}

uint32_t zmedi_node::getCount(char c) {
  return this->counters.at(c);
}

wavelet *zmedi_node::getWave() {
  return this->wave;
}
