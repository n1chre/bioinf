//
// Created by Zvonimir Medic on 28/12/2016.
//
#include "balanced_tree.h"
#include <iostream>

balanced_tree::balanced_tree(std::vector<data *> &nodes) {
  this->size = (uint32_t) nodes.size();
  this->nodes = nodes;
}

// Kolko ima charova kao i prije indexa uint32
const uint32_t balanced_tree::rank(char i, uint32_t idx) const {
  std::cerr << "Trazim:" << idx << std::endl;
  auto it =
      std::lower_bound(nodes.begin(),
                       nodes.end(), idx,
                       [=](auto *ptr, auto val) -> bool {
                         return ptr->get_starting_idx() < idx;
                       });

  //std::cerr << "Imam it: " << (it == nodes.end()) << (*it)->get_starting_idx() << std::endl;
  return (*it)->get_count(i) + (*it)->get_wave()->rank(i, idx - (*it)->get_starting_idx());
}

// koji je index uint32 tog chara kao i
// Prvi koji je manji od indeksa
const uint32_t balanced_tree::select(char i, uint32_t idx) const {
  auto it =
      std::lower_bound(nodes.rbegin(),
                       nodes.rend(), idx,
                       [=](auto *ptr, auto val) -> bool {

                         return ptr->get_count(i) > idx;
                       });

  //std::cerr << "Imam it: " << (it == nodes.rend()) << (*it)->get_starting_idx() << std::endl;
  return (*it)->get_starting_idx() + (*it)->get_wave()->select(i, idx - (*it)->get_count(i));
}
