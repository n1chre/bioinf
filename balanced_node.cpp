//
// Created by Zvonimir Medic on 28/12/2016.
//

#include "balanced_node.h"

balanced_node::balanced_node(data *d) {
  this->d = d;
}

const uint32_t balanced_node::get_count(char c) const {
  return this->d->getCounters().at(c);
}

const wavelet *balanced_node::get_wave() const {
  return this->d->getWave();
}

const uint32_t balanced_node::get_starting_idx(void) const {
  return this->d->getStarting_idx();
}
const uint32_t balanced_node::get_ending_idx(void) const {
  return this->d->getEnding_idx();
}
