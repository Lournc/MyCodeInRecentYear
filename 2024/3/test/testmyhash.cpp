#include <cstdint>
#include <iostream>
#include <random>
const int BUCKET = 15;
uint hash(uint dev, uint blockno) {
  uint a, b, c, d;
  a = (dev | blockno) >> 24;
  b = ((dev | blockno) << 8) >> 24;
  c = ((dev | blockno) << 16) >> 24;
  d = (dev | blockno) & 0b11111111;
  a |= ~c & 0b11111111;
  b |= ~d & 0b11111111;
  return (a + b) % BUCKET;
}

int main() {
  int hasht[BUCKET]{};

  std::random_device rd;  // 随机数引擎的种子源
  std::mt19937 gen(rd()); // 以 rd() 播种的 mersenne_twister_engine
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  for (int i = 0; i < 100000; i++) {
    hasht[hash(distrib(gen), distrib(gen))]++;
  }
  for (int i = 0; i < BUCKET; i++) {
    std::cout << hasht[i] << std::endl;
  }
}