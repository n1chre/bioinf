#include <iostream>
#include "bitset.h"

using std::cout;
using std::endl;

int main() {
  bitset bs(76, 67836432423687234LLU);
  bs[75] = 1;
  bs[64] = 1;
  for (int i = bs.size() - 1; i >= 0; --i) {
    cout << bs[i];
  }
  cout << endl;

  auto x = bs >> 3;

  for (int i = bs.size() - 1; i >= 0; --i) {
    cout << x[i];
  }
  cout << endl;

  return 0;
}