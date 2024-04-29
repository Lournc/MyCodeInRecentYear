#include <algorithm>
#include <format>
#include <iostream>
int partition(int arr[], int p, int r) {
  int x = arr[r];
  int i = p - 1;
  for (int j = p; j < r; j++) {
    if (arr[j] < x) {
      std::swap(arr[i + 1], arr[j]);
      i++;
    }
  }
  std::swap(arr[i + 1], arr[r]);
  return i + 1;
}
int selection(int arr[], int p, int r, int k) {
  int q = partition(arr, p, r);
  int x{};
  if (k == q - p + 1) {
    x = arr[q];
  }
  if (k < q - p + 1) {
    x = selection(arr, p, q - 1, k);
  }
  if (k > q - p + 1) {
    x = selection(arr, q + 1, r, k - q + p - 1);
  }
  return x;
}
int main() {
  // 14 16 29 44 54 57 58 58 63 65 67 70 82 736
  int a[]{73, 58, 54, 65, 57, 82, 70, 58, 67, 63, 29, 16, 44, 14};
  int k;
  std::cout << "输入k\n";
  std::cin >> k;
  std::cout << std::format("第k小数为{}\n", selection(a, 0, 13, k));
  return 0;
}