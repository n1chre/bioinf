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

/**
 * Represents a single wavelet tree.
 * Used to answer rank/select queries.
 * Speed depends on bitmask's underlying implementation
 */
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

  /**
   * Find leaf node which contains only given characters
   *
   * @param c character
   * @return leaf node
   */
  const wavelet *findLeaf(char c) const;

  /**
   * @return is this node a leaf node
   */
  inline const bool leaf() const {
    return left==nullptr && right==nullptr;
  }

  /**
   * Recursive select, goes from leaf to root node
   *
   * @param idx index for select
   * @param b value selected
   * @return final select
   */
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
