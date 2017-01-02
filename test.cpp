//
// Created by Zvonimir Medic on 02/01/2017.
//

#include "test.h"

int main(int argc, char **argv) {
  std::random_device rd;
  srand(rd());

  std::cerr << "Testing bitset... ";
  test_bitset();
  std::cerr << "Pass!" << std::endl;

  std::cerr << "Testing bitmasks... ";
  test_bitmask();
  std::cerr << "Pass!" << std::endl;

  std::cerr << "Testing wavelet... ";
  test_wavelet();
  std::cerr << "Pass!" << std::endl;

  const uint32_t ws = 64;

  std::cerr << "Testing lookup list... ";
  test_rank_select(
      [](std::vector<data *> &v) -> rank_select * { return new lookup_list(v); },
      data::create, ws
  );
  std::cerr << "Pass!" << std::endl;

  std::cerr << "Testing red black tree... ";
  test_rank_select(
      [](std::vector<data *> &v) -> rank_select * { return new rb_tree(v, ws); },
      data::create, ws
  );
  std::cerr << "Pass!" << std::endl;

}