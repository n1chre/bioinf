//
// Created by Zvonimir Medic on 28/12/2016.
//
#include "lookup_list.h"

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
  auto it = std::lower_bound(nodes.rbegin(),
                             nodes.rend(), idx,
                             [&](auto *ptr, auto val) -> bool {
                               return ptr->get_starting_idx() > idx;
                             });
  if (it==nodes.rend()) {
    throw std::out_of_range("invalid index");
  }
  data *d = *it;
  return d->get_count(i) + d->get_wave()->rank(i, idx - d->get_starting_idx());
}

const uint32_t lookup_list::select(char i, uint32_t idx) const {
  auto it = std::lower_bound(nodes.rbegin(),
                             nodes.rend(), idx,
                             [&](auto *ptr, auto val) -> bool {
                               return ptr->get_count(i) >= idx;
                             });
  if (it==nodes.rend()) {
    throw std::out_of_range("no such element");
  }
  data *d = *it;

  uint32_t s;
  try {
    s = d->get_wave()->select(i, idx - d->get_count(i));
  } catch (const std::invalid_argument &) {
    throw std::out_of_range("no such element");
  }

  return d->get_starting_idx() + s;
}
