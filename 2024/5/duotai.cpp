#include <iostream>
struct A {
  int a = 1;
  virtual void f() { std::cout << "A::f()" << a << std::endl; }
};

struct B : A {
  int b = 2;
  void f() override { std::cout << "B::f()" << a << b << std::endl; }
};

void f(A &a) { a.f(); }

int main() {
  B b = B();
  A a = b;
  a.f();
  f(b);
}
