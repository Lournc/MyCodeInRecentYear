#include <iostream>
#include <random>

int main() {
  std::random_device rd;  // 随机数引擎的种子源
  std::mt19937 gen(rd()); // 以 rd() 播种的 mersenne_twister_engine
  std::uniform_int_distribution<> distrib(1, 6);

  // 用 distrib 变换 gen 所生成的随机 unsigned int 为 [1, 6] 中的 int
  for (int n = 0; n != 10; ++n)
    std::cout << distrib(gen) << ' ';
  std::cout << '\n';
}