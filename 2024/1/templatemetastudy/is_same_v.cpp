#include <iostream>
namespace koarz {

struct true_type {
  constexpr static bool value{true};
};

struct false_type {
  constexpr static bool value{false};
};

template <typename T, typename U> struct is_same_v : false_type {};

template <typename T> struct is_same_v<T, T> : true_type {};

} // namespace koarz
int main() {
  std::cout << koarz::is_same_v<int, double>::value << std::endl;
  std::cout << koarz::is_same_v<int, int>::value << std::endl;
  std::cout << koarz::is_same_v<double, double>::value << std::endl;
  return 0;
}