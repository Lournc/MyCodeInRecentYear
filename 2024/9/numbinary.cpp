#include <bitset>
#include <cstring>
#include <iostream>

template <typename T> void printNumBinary(T num) {
  unsigned char bytes[sizeof(T)];
  std::memcpy(bytes, &num, sizeof(T));
  for (int i = sizeof(T) - 1; i >= 0; --i) {
    std::bitset<8> bits(bytes[i]);
    std::cout << bits;
  }
  std::cout << std::endl;
}

int main() {
  float num = 137.7; // 示例浮点数
  std::cout << num << '\n';
  printNumBinary(num);
  double num2 = 137.7;
  printNumBinary(num2);
  return 0;
}
