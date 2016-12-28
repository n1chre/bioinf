//
// Created by Zvonimir Medic on 28/12/2016.
//
#include "balanced_tree.h"

balanced_tree::balanced_tree(std::vector<balanced_node *> &nodes) {
  this->size = nodes.size();
  this->nodes = nodes;
}

// Kolko ima charova kao i prije indexa uint32
const uint32_t balanced_tree::rank(char i, uint32_t idx) const {
  auto it =
      *std::lower_bound(nodes.begin(),
                        nodes.end(), idx,
                        [](balanced_node *&ptr, uint32_t val) -> {
                          return ptr->get_starting_idx() >= idx;
                        });
  return it->get_wave()->rank(i, idx - it->get_starting_idx());
}

// koji je index uint32 tog chara kao i
const uint32_t balanced_tree::select(char i, uint32_t idx) const {
  auto it =
      *std::lower_bound(nodes.rbegin(),
                        nodes.rend(), idx,
                        [](balanced_node *&ptr, uint32_t val) -> {
                          return ptr->get_count(i) < idx;
                        });
  return it->get_wave()->select(i, idx - it->get_count(i));
}
