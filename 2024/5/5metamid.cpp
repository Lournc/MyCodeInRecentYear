#include <algorithm>
#include <iostream>
#include <vector>

int sort5(int *arr, int l, int r) {
  std::sort(arr + l, arr + r);
  return arr[(r + l) / 2];
}

int partition(int *arr, int pivot, int size) {
  int l = 0;
  int r = size - 1;
  for (int i = 1; i <= r;) {
    if (arr[i] == pivot) {
      i++;
    } else if (arr[i] < pivot) {
      std::swap(arr[i], arr[l]);
      l++;
      i++;
    } else {
      std::swap(arr[i], arr[r]);
      r--;
    }
  }
  return l;
}

int select(int *arr, int k, int size) {
  std::vector<int> c;
  for (int i = 0; i < size / 5; i++) {
    c.push_back(sort5(arr, i * 5, std::min(size, i * 5 + 5)));
  }
  std::sort(c.begin(), c.end());
  int pivot = c[c.size() / 2];
  int p = partition(arr, pivot, size);
  if (p == k)
    return pivot;
  if (k < p)
    return select(arr, k, p);
  return select(arr + p + 1, k - p - 1, size - p);
}

int main() {
  //
  int arr[]{4, 6, 10, 5, 7, 26, 31, 14, 9, 7, 3, 5, 8, 37, 28};
  // 找第8小元素
  std::cout << select(arr, 8, 15);
  return 0;
}