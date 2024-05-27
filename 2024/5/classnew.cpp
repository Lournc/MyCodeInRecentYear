class A {
public:
  A() { data = new int(20); }
  ~A() { delete[] data; }
  int *data;
};

#include <iostream>

int main() {
  A a;
  std::cout << *a.data;
  return 0;
}