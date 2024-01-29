#include "is_same_v.hpp"
#include "print.hpp"
#include "tuple.hpp"
#include <iostream>
#include <ostream>
#include <tuple>

int main() {
  koarz::tuple<int, int, double> a(5, 2, 1.0);
  std::tuple<int, int, double> b(5, 2, 0.0);
  std::cout << a.get(0) << ' ' << a.get(1) << ' ' << a.get(2) << ' '
            << sizeof(a) << std::endl;
  std::cout << std::get<0>(b) << ' ' << std::get<1>(b) << ' ' << std::get<2>(b)
            << ' ' << sizeof(b) << std::endl;
  std::cout << koarz::is_same_v<int, double>::value << std::endl;
  std::cout << koarz::is_same_v<int, int>::value << std::endl;
  std::cout << koarz::is_same_v<double, double>::value << std::endl;
  koarz::print("{},{},{},{},{},{}\n", 10, 2.0, 'A', 3.14f, -5, "Hello");
  return 0;
}