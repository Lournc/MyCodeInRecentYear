#include <iostream>

int &f() {
  int a{10};
  return a;
}

int f2() {
  int b{50};
  return b;
}

int main() {
  int &a = f();
  int b = f2();
  std::cout << a;
  int c = 20;
  return 0;
}