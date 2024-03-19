#include <iostream>
template <typename T> constexpr bool is_const_v = false;
template <typename T> constexpr bool is_const_v<const T> = true;

int main() {
  std::cout
      << is_const_v<
             const int
                 *> << is_const_v<const int[1]> << is_const_v<const int **> << is_const_v<const int(*)[1]> << is_const_v<const int *[1]> << is_const_v<const int[1][1]>;
}