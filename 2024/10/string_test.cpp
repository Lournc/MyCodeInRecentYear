#include <format>
#include <iostream>
#include <string>

int main() {
  std::string s = {"I123456 P789\n111223"};
  std::cout << s << ' ' << s.substr(1, s.find(' ')) << '\n' << s.size();
  return 0;
}