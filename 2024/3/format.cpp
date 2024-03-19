#include <format>
#include <iostream>

int main() {
  std::cout << std::format("Hello,{}", "world");
  return 0;
}