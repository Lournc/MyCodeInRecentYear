#include <format>
#include <iostream>
#include <random>
double get_random_real() {
  std::random_device rd;  // 将用于获得随机数引擎的种子
  std::mt19937 gen(rd()); // 以 rd() 播种的标准 mersenne_twister_engine
  std::uniform_real_distribution<> dis(1.0, 10.0);
  return dis(gen);
}

int main() {
  for (int j = 0; j < 40; j++) {
    std::cout << "insert into double_value values ";
    for (int i = 1; i < 250000; i++) {
      std::cout << std::format("({},{},{},{}),", i + 250000 * j,
                               get_random_real(), get_random_real(),
                               get_random_real());
    }
    std::cout << std::format("({},{},{},{});\n", 250000 * (j + 1),
                             get_random_real(), get_random_real(),
                             get_random_real());
  }
  return 0;
}
