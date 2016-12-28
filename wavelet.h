//
// Created by Zvonimir Medic on 28/12/2016.
//
#ifndef BIOINF_ABSTRACT_NODE_H
#define BIOINF_ABSTRACT_NODE_H

#include <cstdint>
#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include "bitmask.h"

//template<typename B, typename std::enable_if<std::is_base_of<bitmask, B>::value>::type * = nullptr>
class wavelet {

 private:
  // main parts
  bitmask *mask;
  std::unordered_map<char, bool> alpha;

  // pointers
  const wavelet *parent;
  wavelet *left;
  wavelet *right;

  wavelet(const wavelet *parent, const std::string &str, const std::string &alphabet);

  const wavelet *findLeaf(char c) const;

  inline const bool leaf() const {
    return left==nullptr && right==nullptr;
  }

  const uint32_t select_rec(uint32_t idx, bool b) const;

 public:

  wavelet(const std::string &str, const std::string &alphabet)
      : wavelet(nullptr, str, alphabet) {};

  const char operator[](uint32_t idx);
  const uint32_t rank(char elem, uint32_t idx) const;
  const uint32_t select(char elem, uint32_t idx) const;
  const uint32_t length(void) const;
};

#endif //BIOINF_WAVELET_H
