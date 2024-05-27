#include <iostream>
#include <random>

int fun() {
  std::random_device rd;  // 随机数引擎的种子源
  std::mt19937 gen(rd()); // 以 rd() 播种的 mersenne_twister_engine
  std::uniform_int_distribution<> distrib(1, 6);
  return distrib(gen) % 2;
}

int main() {
  int arr[2]{};
  for (int i = 0; i < 1000; i++) {
    if (fun())
      arr[0]++;
    else
      arr[1]++;
  }
  std::cout << arr[0] << ' ' << arr[1];
  return 0;
}