#include <cstring>
#include <format>
#include <iostream>

template <const int size, const int max_size>
constexpr int merge_sort(int *arr) {
  int total{};
  int new_arr[size];
  auto f = [&](int ll, int rl) {
    int p{}, l{ll}, r{(rl + l) / 2};
    while (l < (rl + ll) / 2 && r < rl) {
      if (arr[l] < arr[r]) {
        new_arr[p++] = arr[l++];
      } else {
        new_arr[p++] = arr[r++];
      }
      total++;
    }
    if (r == rl) {
      std::memcpy(&new_arr[p], &arr[l], ((rl + ll) / 2 - l) * sizeof(int));
    }
    if (l == (rl + ll) / 2) {
      std::memcpy(&new_arr[p], &arr[r], (rl - r) * sizeof(int));
    }
    std::memmove(&arr[ll], new_arr, size * sizeof(int));
  };
  for (int i = 0; i * size < max_size; i++) {
    f(i * size, i * size + size);
  }
  if constexpr (size == max_size) {
    return total;
  } else {
    return total + merge_sort<size * 2, max_size>(arr);
  }
}

int main() {
  int a[] = {125, 130, 132, 123, 127, 129, 117, 121, 126, 116, 120, 122};
  std::cout << std::format("共比较了：{}次\n", merge_sort<6, std::size(a)>(a));
  for (int &v : a) {
    std::cout << v << ' ';
  }
  return 0;
}