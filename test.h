//
// Created by Filip Hrenic on 02/01/2017.
//
#include <iostream>
#include <cstdint>
#include <string>
#include <cassert>
#include <vector>
#include <random>

#include "bitset.h"
#include "bitmask.h"
#include "bitmask_bitset.h"
#include "bitmask_vector.h"
#include "wavelet.h"
#include "data.h"
#include "rank_select.h"
#include "lookup_list.h"
#include "rb_tree.h"

inline uint32_t __select(const std::string &str, char c, uint32_t idx) {
  if (idx==0) { throw std::out_of_range("no elem"); }
  uint32_t ret = 0;
  for (auto _c : str) {
    if (c==_c) {
      if (--idx==0) {
        return ret;
      }
    }
    ret++;
  }
  throw std::out_of_range("no such elem");
};

inline uint32_t __rank(const std::string &str, char c, uint32_t idx) {
  if (idx >= str.length()) {
    throw std::out_of_range("no such idx");
  }
  auto it = str.begin();
  return (uint32_t) std::count(it, it + idx + 1, c);
};

void test_bitset() {
  bitset b(65);
  b[0] = 1;
  b[63] = 1;
  b[64] = 1;

  assert(b.binary_rank(0)==1);
  assert(b.binary_rank(1)==1);
  assert(b.binary_rank(5)==1);
  assert(b.binary_rank(63)==2);
  assert(b.binary_rank(64)==3);

  assert(b.binary_select(1, true)==0);
  assert(b.binary_select(2, true)==63);
  assert(b.binary_select(3, true)==64);
  try {
    b.binary_select(4, true);
    assert(false);
  } catch (const std::out_of_range &) {
    assert(true);
  }

  for (uint32_t i = 1; i <= 62; ++i) {
    assert(b.binary_select(i, false)==i);
  }

  try {
    b.binary_select(63, false);
    assert(false);
  } catch (const std::out_of_range &) {
    assert(true);
  }

  for (uint32_t i = 1; i <= 65; ++i) {
    try {
      assert(b.binary_rank(b.binary_select(i, true))==i);
    } catch (const std::out_of_range &) {
      break;
    }
  }
}

void test_bitmask() {
  const uint32_t size = 1025;
  bitmask *b = bitmask_bitset::create(size);
  bitmask *v = bitmask_vector::create(size);

  for (uint32_t i = 0; i < 256; i++) {
    auto idx = rand()%size;
    b->set(idx, true);
    v->set(idx, true);
  }

  for (uint32_t i = 0; i < size; i++) {
    assert(b->get(i)==v->get(i));
  }

  auto assert_select = [&](uint32_t idx, bool val) -> void {
    try {
      auto _b = b->select01(idx, val);
      // no exception, v must not throw exception
      try {
        auto _v = v->select01(idx, val);
        assert(_b==_v);
      } catch (const std::out_of_range &) {
        assert(false);
      }
    } catch (const std::out_of_range &) {
      // exception, expect exception too
      try {
        v->select01(idx, val);
        assert(false);
      } catch (const std::out_of_range &) {
        assert(true);
      }
    }
  };

  for (uint32_t j = 0; j < size; ++j) {
    assert(b->rank0(j)==v->rank0(j));
    assert(b->rank1(j)==v->rank1(j));
    assert_select(j, false);
    assert_select(j, true);
  }
}

std::function<void(char, uint32_t)> asserter(
    std::function<uint32_t(char c, uint32_t idx)> select,
    const std::string &str) {

  return [&](char c, uint32_t idx) -> void {
    try {
      auto _b = select(c, idx);
      // no exception, v must not throw exception
      try {
        auto _v = __select(str, c, idx);
        assert(_b==_v);
      } catch (const std::out_of_range &) {
        assert(false);
      }
    } catch (const std::out_of_range &) {
      // exception, expect exception too
      try {
        __select(str, c, idx);
        assert(false);
      } catch (const std::out_of_range &) {
        assert(true);
      }
    }
  };
}

void test_wavelet() {
  const uint32_t alpha_size = 26; // 1-26
  const uint32_t str_size = 1;

  // dont touch rest of this function

  std::string str;
  for (int i = 0; i < str_size; ++i) {
    str += ('A' + rand()%alpha_size);
  }

  bitmask::set_creator(&bitmask_bitset::create);
  wavelet w(str);
  assert(w.length()==str.length());

  for (uint32_t i = 0; i < str_size; ++i) {
    assert(str[i]==w[i]);
  }

  auto assert_select = asserter([&](char c, uint32_t idx) -> uint32_t {
    return w.select(c, idx);
  }, str);

  for (char j = 0; j < 26; ++j) {
    char c = 'A' + j;
    try {
      w.rank(c, 0);
    } catch (const std::invalid_argument &ex) {
      continue;
    }
    for (uint32_t i = 0; i < str_size; ++i) {
      assert_select(c, i);
      assert(__rank(str, c, i)==w.rank(c, i));
      try {
        auto s = w.select(c, i);
        assert(w.rank(c, s)==i);
      } catch (...) {
      }
    }
  }

}

void test_rank_select(
    rank_select *(*create)(std::vector<data *> &),
    data *(*create_data)(std::string &, uint32_t, std::unordered_map<char, uint32_t> &),
    const uint32_t word_size) {
  const uint32_t alpha_size = 4; // 1-26
  const uint32_t str_size = 1025;

  // dont touch rest of this function

  std::string str;
  for (int i = 0; i < str_size; ++i) {
    str += ('A' + rand()%alpha_size);
  }
  std::string for_rs = str;

  bitmask::set_creator(&bitmask_bitset::create);
  std::unordered_map<char, uint32_t> counters;
  std::vector<data *> ds;
  while (for_rs.length()) {
    ds.push_back(create_data(for_rs, word_size, counters));
  }
  rank_select *rs = create(ds);

  for (uint32_t i = 0; i < str_size; ++i) {
    assert(str[i]==(*rs)[i]);
  }

  auto assert_select = asserter([&](char c, uint32_t idx) -> uint32_t {
    return rs->select(c, idx);
  }, str);

  for (char j = 0; j < 26; ++j) {
    char c = 'A' + j;
    try {
      rs->rank(c, 0);
    } catch (const std::invalid_argument &ex) {
      continue;
    }
    for (uint32_t i = 0; i < str_size; ++i) {
      assert_select(c, i);
      assert(__rank(str, c, i)==rs->rank(c, i));
      try {
        auto s = rs->select(c, i);
        assert(rs->rank(c, s)==i);
      } catch (...) {
      }
    }
  }
}

