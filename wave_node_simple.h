//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_WAVE_H
#define BIOINF_WAVE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <map>
#include <vector>

class wave_node_simple {

 private:

  // main parts
  std::vector<bool> mask;
  std::map<char, bool> alpha;

  // pointers
  const wave_node_simple *parent;
  wave_node_simple *left;
  wave_node_simple *right;

  wave_node_simple(const wave_node_simple *parent, const std::string &str, const std::string &alphabet);

  inline const uint32_t rank0(uint32_t idx) {
    auto it = mask.begin();
    return (uint32_t) std::count(it, it + idx, false);
  }

  inline const uint32_t rank1(uint32_t idx) {
    return idx - rank0(idx);
  }

  inline const bool leaf() {
    return left == nullptr && right == nullptr;
  }

 public:

  wave_node_simple(const std::string &str, const std::string &alphabet)
      : wave_node_simple(nullptr, str, alphabet) {};

  const char operator[](uint32_t idx);
  const uint32_t rank(char elem, uint32_t idx);
  const uint32_t select(char elem, uint32_t occ);

};

#endif //BIOINF_WAVE_H
