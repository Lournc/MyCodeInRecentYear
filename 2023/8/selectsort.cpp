#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
int main() {
  int arr[]{12, 6, 84, 45, 12, 36, 98, 74, 10, 11, 1, 3};
  for (int i = 0; i < std::size(arr) - 1; i++) {
    std::swap(*std::min_element(&arr[i], std::end(arr)), arr[i]);
  }
  for (int i = 0; i < std::size(arr); i++) {
    std::cout << arr[i] << ' ';
  }
  return 0;
}