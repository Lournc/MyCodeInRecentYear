#include <iostream>

int main() {
  int arr[50];
  int *p = arr;
  std::cout << sizeof(arr) << ' ' << sizeof(p);
}