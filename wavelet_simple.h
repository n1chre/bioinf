//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_WAVE_H
#define BIOINF_WAVE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class wavelet_simple {

 private:
  // main parts
  std::vector<bool> mask;
  std::unordered_map<char, bool> alpha;

  // pointers
  const wavelet_simple *parent;
  wavelet_simple *left;
  wavelet_simple *right;

  wavelet_simple(const wavelet_simple *parent, const std::string &str, const std::string &alphabet);

  inline const uint32_t rank0(uint32_t idx) {
    auto it = mask.begin();
    return (uint32_t) std::count(it, it + idx, false);
  }

  inline const uint32_t rank1(uint32_t idx) {
    return idx - rank0(idx);
  }

  inline const uint32_t select_rec(uint32_t idx, bool b) const;

  inline const uint32_t select01(uint32_t idx, bool b) const {
    uint32_t sol = 0;
    for (auto it = mask.begin(); it!=mask.end(); it++) {
      if (*it==b) {
        if (idx--==0) {
          return sol;
        }
      }
      sol++;
    }
    throw -1;
  }

  const wavelet_simple *findLeaf(char c);

 private:

  inline const bool leaf() {
    return left==nullptr && right==nullptr;
  }

 public:

  wavelet_simple(const std::string &str, const std::string &alphabet)
      : wavelet_simple(nullptr, str, alphabet) {};

  const char operator[](uint32_t idx);
  const uint32_t rank(char elem, uint32_t idx);
  const uint32_t select(char elem, uint32_t idx);

};

#endif //BIOINF_WAVE_H
