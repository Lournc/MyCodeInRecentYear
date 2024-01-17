#include <iostream>
using namespace std;

class A {
public:
  A() { cout << "A()\n"; }
  ~A() { cout << "~A()\n"; }
};

void fun2() {
  cout << "fun2 begin\n";
  A b;
  cout << "fun2 end\n";
}

void fun1() {
  cout << "fun1 begin\n";
  fun2();
  cout << "fun1 end\n";
}

int main() {
  cout << "main begin\n";
  fun1();
  cout << "main end\n";
  return 0;
}