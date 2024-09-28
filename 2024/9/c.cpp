#include <boost/type_index.hpp>
#include <cmath>
#include <cstdio>
#include <iostream>

int main() {
  std::cout << (std::fabs(0.1 + 0.1 + 0.1 - 0.3) < 1e-6);
  return 0;
}