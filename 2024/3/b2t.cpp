#include <cstring>
#include <iostream>

int main() {
  char a[100]{};
  int b{};
  std::cin >> a;
  for (int i = 0; i < strlen(a); i++) {
    b = (b << 1) + a[i] - '0';
  }
  std::cout << b;
}