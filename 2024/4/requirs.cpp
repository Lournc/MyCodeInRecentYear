#include <iostream>
#include <type_traits>

template <typename Datatype>
  requires std::is_same_v<Datatype, int>
void f(Datatype v) {
  std::cout << "int";
}

template <typename Datatype>
  requires(!std::is_same_v<Datatype, int>)
void f(Datatype v) {
  std::cout << "other";
}

int main() {
  f(1);
  f(2.0);
  return 0;
}