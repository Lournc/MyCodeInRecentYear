#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using namespace std::literals;
int work() {
  std::this_thread::sleep_for(2s);
  return 10;
}

int work2() {
  std::this_thread::sleep_for(1s);
  return 2;
}

void work3(std::promise<int> &prom) {
  std::this_thread::sleep_for(1s);
  prom.set_value(5);
  std::this_thread::sleep_for(1s);
  std::cout << "work3 done\n";
}
int main() {
  auto fut = std::async(std::launch::async, work);
  auto fut2 = std::async(std::launch::async, work2);
  std::cout << "Waiting for work done... ,get a num is " << fut.get() << '\n';
  std::cout << "Something\n";
  std::cout << fut2.get();
  std::promise<int> prom;
  auto fut3 = prom.get_future();
  std::jthread th(work, prom);
  std::cout << "promise val is " << fut.get();
  return 0;
}