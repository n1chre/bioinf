//
// Created by Zvonimir Medic on 28/12/2016.
//
#include "lookup_list.h"
#include <iostream>

lookup_list::lookup_list(std::vector<data *> &nodes) {
  this->size = (uint32_t) nodes.size();
  this->nodes = nodes;
}

const char lookup_list::operator[](const uint32_t idx) const {
  auto it = *std::lower_bound(nodes.rbegin(),
                              nodes.rend(), idx,
                              [&](auto *ptr, auto val) -> bool {
                                return ptr->get_starting_idx() > idx;
                              });
  return (*it->get_wave())[idx - it->get_starting_idx()];
}

const uint32_t lookup_list::rank(char i, uint32_t idx) const {
  auto it = *std::lower_bound(nodes.rbegin(),
                              nodes.rend(), idx,
                              [&](auto *ptr, auto val) -> bool {
                                return ptr->get_starting_idx() > idx;
                              });
  return it->get_count(i) + it->get_wave()->rank(i, idx - it->get_starting_idx());
}

const uint32_t lookup_list::select(char i, uint32_t idx) const {
  auto it = *std::lower_bound(nodes.rbegin(),
                              nodes.rend(), idx,
                              [&](auto *ptr, auto val) -> bool {
                                return ptr->get_count(i) > idx;
                              });
  return it->get_starting_idx() + it->get_wave()->select(i, idx - it->get_count(i));
}
