#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

__attribute__((pure)) unsigned int index_check_const(unsigned int arg,
                                                     bool constancy) noexcept {
  if (constancy) {
    return 0;
  }
  return arg;
}
using Int32 = int32_t;

void f(std::vector<double> &col1, std::vector<double> &col2,
       const bool is_const[]) {
  uint size = col1.size();
  for (int i = 0; i < size; i++) {
    double a = col1[index_check_const(i, is_const[0])];
    std::cout << "a " << a;
    double b = col2[index_check_const(i, is_const[1])];
    std::cout << "b " << b << '\n';
  }
}

int main() {
  std::vector<double> col1;
  std::vector<double> col2;
  int k;
  for (int i = 0; i < 4; i++) {
    std::cin >> k;
    col1.push_back(k);
  }
  std::cin >> k;
  col2.push_back(k);
  bool is_const[]{col1.size() == 1, col2.size() == 1};
  f(col1, col2, is_const);
}