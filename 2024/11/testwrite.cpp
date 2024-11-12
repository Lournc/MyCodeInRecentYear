#include <fstream>

int main() {
  std::fstream file("example.bin", std::ios::out | std::ios::binary);
  if (file) {
    file.seekp(1000); // 将写指针移动到偏移量 1000
    file.put('A');    // 写入单个字符 'A'
    file.close();
  }
  return 0;
}
