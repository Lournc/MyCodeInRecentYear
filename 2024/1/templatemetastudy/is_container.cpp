#include <iostream>
#include <iterator>
#include <vector>


template <typename T> 
constexpr bool is_container_v() {
    if constexpr(std::begin(T)) {
        return true;
    }
    return false;
};

template <typename T>
inline constexpr bool is_container = is_container_v<T>();

int main() {
    std::vector<int> a;
  std::cout << is_container<std::vector<int>> << ' ' << is_container<int>;
  return 0;
}