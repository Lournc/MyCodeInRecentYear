#include <iostream>

int main() {
  const char *hi = "Hi";
  int a = 10;
  int *b = &a;
  std::cout << hi << ' ' << b << '\n';
}