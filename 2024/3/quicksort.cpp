#include <iostream>
#include <sys/types.h>

void quicksort(int arr[], uint l, uint r) {
  if (l >= r) {
    return;
  }
  uint i{l}, j{l};
  while (j < r) {
    if (arr[j] <= arr[r]) {
      if (i != j) {
        std::swap(arr[j], arr[i]);
        // 交换时i指的是第一个>=arr[r]的元素
      }
      i++;
    }
    j++;
  }
  std::swap(arr[i], arr[r]);
  quicksort(arr, l, i - 1);
  quicksort(arr, i + 1, r);
}

int main() {
  int arr[]{2, 4, 5, 2, 6, 85, 5, 2, 11, 4, 41, 11, 2, 132, 13, 42};
  quicksort(arr, 0, std::size(arr) - 1);
  for (int &v : arr) {
    std::cout << v << ' ';
  }
  return 0;
}