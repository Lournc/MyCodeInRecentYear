#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

// 这个例子说明 使用condition_variable.wait在判断条件失败时会释放lock
// 在唤醒时会重新获取lock
int main() {
  std::condition_variable cv;
  std::mutex mut;
  bool condition{};
  std::thread t1([&]() {
    std::unique_lock<std::mutex> lock(mut);
    std::cout << "cv wait\n";
    cv.wait(lock, [&]() { return condition; });
    std::cout << "C V wait end\n";
  });
  std::thread t2([&]() {
    std::unique_lock<std::mutex> lock(mut);
    std::cout << "Main function\n";
    condition = true;
    cv.notify_one();
  });

  t1.join();
  t2.join();
  return 0;
}