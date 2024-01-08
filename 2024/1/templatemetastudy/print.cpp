#include <format>
#include <iostream>
#include <string>
#include <string_view>
namespace koarz {

template <typename... T> void print(std::string_view fmt, T... v) {
  std::cout << std::vformat(fmt, std::make_format_args(v...));
}

} // namespace koarz
int main() {
  koarz::print("{},{},{},{},{},{}\n", 10, 2.0, 'A', 3.14f, -5, "Hello");
  return 0;
}