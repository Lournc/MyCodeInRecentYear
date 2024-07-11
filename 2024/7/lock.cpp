#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic_int total;
namespace koarz {
class spin_lock {
  std::atomic_bool locked{false};

public:
  void lock() {
    bool t{false};
    while (!locked.compare_exchange_weak(t, true)) {
      t = false;
    }
  }
  void unlock() { locked = false; }
};
class mutex {
  std::atomic_bool locked{false};

public:
  void lock() {
    bool t{false};
    while (!locked.compare_exchange_weak(t, true)) {
      total++;
      locked.wait(true);
      t = false;
    }
  }
  void unlock() {
    locked = false;
    locked.notify_one();
  }
};
class rwlock {
  std::atomic_int total_{};

public:
  void read_lock() {
    while (true) {
      int t{total_};
      if (t < 0) {
        continue;
      }
      if (total_.compare_exchange_weak(t, t + 1)) {
        return;
      }
    }
  }
  void write_lock() {
    int t{0};
    while (!total_.compare_exchange_weak(t, -1)) {
      t = 0;
    }
  }
  void unlock() {
    int t{-1};
    if (!total_.compare_exchange_weak(t, 0)) {
      total_--;
    }
  }
};
} // namespace koarz

int main() {
  int v{};
  koarz::rwlock lock;
  std::vector<std::thread> ths, rts;
  for (int i = 0; i < 10; i++) {
    ths.emplace_back([&]() {
      lock.write_lock();
      for (int i = 0; i < 100000; i++) {
        v++;
      }
      lock.unlock();
    });
  }
  for (int i = 0; i < 10; i++) {
    rts.emplace_back([&]() {
      lock.read_lock();
      for (int i = 0; i < 100; i++) {
      }
      std::cout << v << ' ';
      lock.unlock();
    });
  }
  std::thread t1([&]() {
    for (auto &t : ths) {
      t.join();
    }
  });
  std::thread t2([&]() {
    for (auto &t : rts) {
      t.join();
    }
  });
  t1.join();
  t2.join();
  std::cout << v;
  return 0;
}