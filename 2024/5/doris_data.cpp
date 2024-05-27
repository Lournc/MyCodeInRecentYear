#include <format>
#include <iostream>
#include <random>
#include <string>
double get_random_real() {
  std::random_device rd;  // 将用于获得随机数引擎的种子
  std::mt19937 gen(rd()); // 以 rd() 播种的标准 mersenne_twister_engine
  std::uniform_real_distribution<> dis(1.0, 10.0);
  return dis(gen);
}

int main() {
  for (int j = 0; j < 40; j++) {
    std::cout << "insert into const_test values ";
    for (int i = 1; i < 250000; i++) {
      std::cout << std::format("({},1.0,{}),", i + 250000 * j,
                               get_random_real());
    }
    std::cout << std::format("({},1.0,{});\n", 250000 * (j + 1),
                             get_random_real());
  }
  return 0;
}
