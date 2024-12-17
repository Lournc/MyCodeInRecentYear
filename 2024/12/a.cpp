#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;
int tickets{10000};
mutex lk;
int main() {
  vector<thread> ts;
  for (int i = 0; i < 4; i++) {
    ts.emplace_back([&] {
      int t{};
      while (true) {
        lk.lock();
        if (tickets == 0) {
          lk.unlock();
          break;
        }
        tickets--;
        t++;
        lk.unlock();
      }
      cout << "Get " << t << "tickets\n";
    });
  }

  for (auto &t : ts) {
    t.join();
  }
}