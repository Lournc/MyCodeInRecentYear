#include <iostream>
int main() {
  int a[] = {9, 5, 5, 4, 12, 32, 2, 78, 65};
  for (int i = 1; i < std::size(a); i++) {
    int b = i;
    for (int j = i - 1; j >= 0; j--) {
      if (a[b] < a[j]) {
        std::swap(a[b--], a[j]);
      }
    }
  }
  for (int i = 0; i < std::size(a); i++) {
    std::cout << a[i] << ' ';
  }
  return 0;
}