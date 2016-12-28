//
// Created by Zvonimir Medic on 28/12/2016.
//
#include "balanced_tree.h"

balanced_tree::balanced_tree(std::vector<balanced_node *> &nodes) {
  this->size = nodes.size();
  this->nodes = nodes;
}

// Kolko ima charova kao i prije indexa uint32
const uint32_t balanced_tree::rank(char i, uint32_t idx) {
  auto it =
      std::lower_bound(nodes.begin(),
                       nodes.end(), idx,
                       [](balanced_node *&ptr, uint32_t val) -> bool { return true; });

  return 0;
}

// koji je index uint32 tog chara kao i
const uint32_t balanced_tree::select(char i, uint32_t idx) {
  return 0;
}
