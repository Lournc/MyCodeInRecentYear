#include <iostream>
namespace koarz {

template <typename T> constexpr bool is_integral_v(T v) { return false; }
template <> constexpr bool is_integral_v<int>(int v) { return true; }
template <typename... T> constexpr bool is_integral(T... v) {
  return (true & (is_integral_v(v) & ...));
}

} // namespace koarz

int main() {
  std::cout << koarz::is_integral(1, 4, 5, 6, 8, 7) << std::endl;
  std::cout << koarz::is_integral(3, 5, 2, 1.0, 4) << std::endl;
  std::cout << koarz::is_integral(3, 5, 2, 'A', 4) << std::endl;
  return 0;
}