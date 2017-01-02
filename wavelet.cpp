//
// Created by Filip Hrenic on 28/12/2016.
//

#include "wavelet.h"
#include <unordered_set>

// private

wavelet::wavelet(const wavelet *parent, const std::string &str) : parent(parent) {

  mask = bitmask::create((uint32_t) str.length());

  // create alphabet
  std::unordered_set<char> chars;
  std::copy(str.begin(), str.end(), std::inserter(chars, chars.end()));
  std::string alphabet;
  std::copy(chars.begin(), chars.end(), std::back_inserter(alphabet));

  if (alphabet.length()==1) {
    alpha[alphabet[0]] = false;
    left = nullptr;
    right = nullptr;
    return;
  }

  std::string sleft, sright;
  uint8_t half = (uint8_t) (alphabet.length()/2);

  for (uint32_t i = 0; i < alphabet.length(); ++i) {
    bool right = i >= half;
    char a = alphabet[i];
    alpha[a] = right;
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

  left = new wavelet(this, sleft);
  right = new wavelet(this, sright);
}

// public

const char wavelet::operator[](uint32_t idx) {
  // leaf node
  if (leaf()) { return alpha.begin()->first; }

  // recurse
  if (mask->get(idx)) { return (*right)[mask->rank1(idx) - 1]; }
  else { return (*left)[mask->rank0(idx) - 1]; }
}

const uint32_t wavelet::rank(char elem, uint32_t idx) const {
  if (!has_elem(elem)) { return 0; }

  if (leaf()) { return mask->rank0(idx); }

  uint32_t rnk;
  if (alpha.at(elem)) {
    rnk = mask->rank1(idx);
  } else {
    rnk = mask->rank0(idx);
  }

  if (rnk--==0) { return 0; }
  return (alpha.at(elem) ? right : left)->rank(elem, rnk);
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
    _idx = parent->select_rec(_idx + 1, (this==parent->right));
  }
  return _idx;
}

const uint32_t wavelet::select(char elem, uint32_t idx) const {
  if (!has_elem(elem)) {
    throw std::invalid_argument("Wavelet doesn't have that letter");
  }
  return findLeaf(elem)->select_rec(idx, false);
}
const uint32_t wavelet::length(void) const {
  return mask->size();
}
