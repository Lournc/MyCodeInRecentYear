#include <iostream>

int main() {
  int a = 100;
  a += a *= a /= a - 6;
  std::cout << a;
}