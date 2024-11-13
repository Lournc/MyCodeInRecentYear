#include <bits/stdc++.h>
using namespace std;

int main() {
  size_t size = 0x135000;
  char s[sizeof(size_t) + 1]{};
  memcpy(s, &size, sizeof(s));
  std::cout << std::string(s, sizeof(size));
  return 0;
}