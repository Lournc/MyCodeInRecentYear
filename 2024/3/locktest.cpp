#include <iostream>
#include <mutex>
#include <thread>

bool is_locked{};
std::mutex mu;

void fun1() {
  for (int i = 0; i < 10; i++) {
    mu.lock();
    is_locked = true;
    std::cerr << i;
  }
}

void fun2() {
  for (int i = 0; i < 10; i++) {
    while (!is_locked)
      std::cerr << '.';
    mu.unlock();
    is_locked = false;
  }
}

int main() {
  std::thread t1(fun1), t2(fun2);
  t1.join();
  t2.join();
  return 0;
}