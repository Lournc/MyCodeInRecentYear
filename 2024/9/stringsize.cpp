#include <iostream>
#include <string>

int main() {
  std::string s{0x30, 0x0d, 0x62, 0x00, 0x61, 0x00, 0x00};
  std::cout << s.size() << "      " << s;
  return 0;
}