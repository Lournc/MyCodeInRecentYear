#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
// class Mutex {
//   std::atomic_bool is_locked_{false};

// public:
//   void Lock();
//   void UnLock();
// };

// void Mutex::Lock() {
//   bool x = false;
//   while (is_locked_.compare_exchange_strong(x, !x))
//     ;
// }

// void Mutex::UnLock() { is_locked_ = false; }

// Mutex mutex;
// int a;
// void f() {
//   mutex.Lock();
//   for (int i = 0; i < 1000; i++) {
//     a++;
//     std::cout << a << std::endl;
//   }
//   mutex.UnLock();
// }

// int main() {
//   std::vector<std::thread> v;
//   for (int i = 0; i < 100; i++) {
//     v.emplace_back(f);
//   }
//   for (int i = 0; i < 100; i++) {
//     v[i].join();
//   }
//   return 0;
// }
int a;
std::atomic_bool is_locked_{false};
void f() {
  bool x = false;
  while (is_locked_.compare_exchange_strong(x, !x))
    std::cout << a++ << std::endl;
  is_locked_ = false;
}
int main() {
  std::mutex mu;
  std::vector<std::thread> v;
  for (int i = 0; i < 100; i++) {
    v.emplace_back(f);
  }
  for (int i = 0; i < 100; i++) {
    v[i].join();
  }
}
