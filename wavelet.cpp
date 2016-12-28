//
// Created by Filip Hrenic on 28/12/2016.
//

#include "wavelet.h"
#include <iostream>

// private

wavelet::wavelet(const wavelet *parent, const std::string &str, const std::string &alphabet) : parent(parent) {

  mask = bitmask::create((uint32_t) str.length());

  if (alphabet.length()==1) {
    alpha[alphabet[0]] = false;
    left = nullptr;
    right = nullptr;
    return;
  }

  std::string aleft, aright, sleft, sright;
  uint8_t half = (uint8_t) (alphabet.length()/2);

  for (uint32_t i = 0; i < alphabet.length(); ++i) {
    bool right = i >= half;
    char a = alphabet[i];
    alpha[a] = right;
    if (right) {
      aright += a;
    } else {
      aleft += a;
    }
  }

  for (uint32_t j = 0; j < str.length(); ++j) {
    char c = str[j];
    bool right = alpha[c];
    mask->set(j, right);
    if (right) {
      sright += c;
    } else {
      sleft += c;
    }
  }

  std::cout << sleft << " " << aleft << std::endl;
  std::cout << sright << " " << aright << std::endl;

  left = new wavelet(this, sleft, aleft);
  right = new wavelet(this, sright, aright);
}

// public

const char wavelet::operator[](uint32_t idx) {
  // leaf node
  if (leaf()) { return alpha.begin()->first; }

  // recurse
  if (mask->get(idx)) { return (*right)[mask->rank1(idx)]; }
  else { return (*left)[mask->rank0(idx)]; }
}

const uint32_t wavelet::rank(char elem, uint32_t idx) const {
  if (leaf()) { return mask->rank0(idx); }

  if (mask->get(idx)) { return right->rank(elem, mask->rank1(idx)); }
  else { return left->rank(elem, mask->rank0(idx)); }
}

const wavelet *wavelet::findLeaf(char c) const {
  if (leaf()) {
    return this;
  }

  return (alpha.at(c) ? right : left)->findLeaf(c);
}

const uint32_t wavelet::select_rec(uint32_t idx, bool b) const {
  uint32_t _idx = mask->select01(idx, b);
  if (parent!=nullptr) {
    _idx = parent->select_rec(_idx, (this==parent->right));
  }
  return _idx;
}

const uint32_t wavelet::select(char elem, uint32_t idx) const {
  return findLeaf(elem)->select_rec(idx, false);
}
const uint32_t wavelet::length(void) const {
  return mask->size();
}
