#include <iostream>
static class A {
public:
  static int a;
  static int get() { return a; }
} a;

int main() {
  a.a = 10;
  std::cout << a.get();
}
// 事实证明class前不能加static