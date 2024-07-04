#include <condition_variable>
#include <cstddef>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>

class A {
public:
  std::queue<int> queue_;
};
size_t size = 10;
class B {
public:
  using it = std::function<void()>;
  B() : v(size) {}

  std::vector<A> v;
};

int main() {
  B b;
  return 0;
}