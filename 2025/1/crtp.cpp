// https://www.youtube.com/watch?v=pmdwAf6hCWg

#include <bits/stdc++.h>
#include <concepts>

// CRTP 的一种替换方法
class AnimalTag {};

template <typename T>
// 如果不使用 derived_from 那么这里就可能被一些鸭子类型调用
concept Animal = requires(T animal) { animal.make_sound(); } &&
                 std::derived_from<T, AnimalTag>;

template <Animal T> void Print(T const &animal) { animal.make_sound(); }

class Sheep : public AnimalTag {
public:
  void make_sound() const { std::cout << "咩咩咩\n"; }
};

int main() {
  Sheep sheep;
  Print(sheep);
  return 0;
}