#include <iostream>
#include <thread>
#include <vector>

// volatile variable not thread safe!
int main() {
  volatile int a{};
  std::vector<std::thread> threads;
  for (int i = 0; i < 16; i++) {
    threads.emplace_back([&a] {
      for (int i = 0; i < 100000; i++)
        a++;
    });
  }
  for (auto &t : threads) {
    t.join();
  }
  std::cout << a;
}