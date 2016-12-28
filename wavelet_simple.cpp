//
// Created by Filip Hrenic on 28/12/2016.
//

#include "wavelet_simple.h"

// private

wavelet_simple::wavelet_simple(const wavelet_simple *parent,
                               const std::string &str,
                               const std::string &alphabet)
    : parent(parent) {

  if (alphabet.length()==1) {
    alpha[alphabet[0]] = false;
    mask.assign(str.length(), false);
    left = nullptr;
    right = nullptr;
    return;
  }

  std::string aleft, aright, sleft, sright;

  uint8_t half = (uint8_t) (alphabet.length()/2);
  uint8_t i = 0;
  for (char a : alphabet) {
    bool right = i++ >= half;
    alpha[a] = right;
    if (right) { aright += a; }
    else { aleft += a; }
  }

  for (int j = 0; j < str.length(); ++j) {
    char c = str[j];
    bool right = alpha[c];
    mask[j] = right;
    if (right) { sright += c; }
    else { sleft += c; }
  }

  left = new wavelet_simple(this, sleft, aleft);
  right = new wavelet_simple(this, sright, aright);
}

// public

const char wavelet_simple::operator[](uint32_t idx) {
  // leaf node
  if (leaf()) { return alpha.begin()->first; }

  // recurse
  if (mask[idx]) { return (*right)[rank1(idx)]; }
  else { return (*left)[rank0(idx)]; }
}

const uint32_t wavelet_simple::rank(char elem, uint32_t idx) const {
  if (leaf()) { return rank0(idx); }

  if (alpha.at(idx)) { return right->rank(elem, rank1(idx)); }
  else { return left->rank(elem, rank0(idx)); }
}

const wavelet_simple *wavelet_simple::findLeaf(char c) const {
  if (leaf()) {
    return this;
  }

  return (alpha.at(c) ? right : left)->findLeaf(c);
}

const uint32_t wavelet_simple::select_rec(uint32_t idx, bool b) const {
  uint32_t _idx = select01(idx, b);
  if (parent!=nullptr) {
    _idx = parent->select_rec(_idx, (this==parent->right));
  }
  return _idx;
}

const uint32_t wavelet_simple::select(char elem, uint32_t idx) const {
  return findLeaf(elem)->select_rec(idx, false);
}
const uint32_t wavelet_simple::length(void) const {
  return (uint32_t) mask.size();
}

