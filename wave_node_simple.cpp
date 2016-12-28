//
// Created by Filip Hrenic on 28/12/2016.
//

#include "wave_node_simple.h"

// private

wave_node_simple::wave_node_simple(const wave_node_simple *parent,
                                   const std::string &str,
                                   const std::string &alphabet) : parent(parent) {

  if (alphabet.length() == 1) {
    alpha[alphabet[0]] = false;
    mask.assign(str.length(), false);
    left = nullptr;
    right = nullptr;
    return;
  }

  std::string aleft, aright, sleft, sright;

  uint8_t half = (uint8_t) (alphabet.length() / 2);
  uint8_t i = 0;
  for (char a : alphabet) {
    bool right = i++ >= half;
    alpha[a] = right;
    if (right) aright += a;
    else aleft += a;
  }

  for (char c : str) {
    bool right = alpha[c];
    mask.push_back(right);
    if (right) sright += c;
    else sleft += c;
  }

  left = new wave_node_simple(this, sleft, aleft);
  right = new wave_node_simple(this, sright, aright);
}

// public

const char wave_node_simple::operator[](uint32_t idx) {
  // leaf node
  if (leaf()) return alpha.begin()->first;

  // recurse
  if (mask[idx]) return (*right)[rank1(idx)];
  else return (*left)[rank0(idx)];
}

const uint32_t wave_node_simple::rank(char elem, uint32_t idx) {
  if (leaf()) return rank0(idx);

  if (alpha[idx]) return right->rank(elem, rank1(idx));
  else return left->rank(elem, rank0(idx));
}

const uint32_t wave_node_simple::select(char elem, uint32_t occ) {
  return 0;
}
