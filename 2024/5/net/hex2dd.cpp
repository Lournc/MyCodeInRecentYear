#include <cstdint>
#include <iostream>
#include <string>
int main(int argc, char **argv) {
  std::string str(argv[1]), res;
  bool flag{false};
  uint32_t val{};
  for (char &v : str.substr(2, str.size() - 2)) {
    val <<= 4;
    if (v > 'a') {
      val += v - 'a' + 10;
    } else {
      val += v - '0';
    }
    if (flag) {
      res += std::to_string(val) + '.';
      val = 0;
    }
    flag ^= 1;
  }
  res.pop_back();
  std::cout << res;
  return 0;
}