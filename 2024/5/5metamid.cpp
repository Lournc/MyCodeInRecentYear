#include <algorithm>
#include <iostream>
#include <vector>

// 五元中值组取中值函数
int media(std::vector<int> &arr, int left, int right) {
  if (right - left < 5) {
    std::sort(arr.begin() + left, arr.begin() + right + 1);
    return arr[left + (right - left) / 2];
  }

  // 将数组分为若干个五元组，并找出每个五元组的中值
  for (int i = left; i <= right; i += 5) {
    int subright = std::min(i + 4, right);
    std::sort(arr.begin() + i, arr.begin() + subright + 1);
    int median = i + (subright - i) / 2;
    std::swap(arr[left + (i - left) / 5], arr[median]);
  }

  // 递归找中值
  int mid = (right - left) / 10 + left + 1;
  return media(arr, left, left + (right - left) / 5);
}

// 分区函数
int partition(std::vector<int> &arr, int left, int right, int pivot) {
  while (left <= right) {
    while (arr[left] < pivot)
      left++;
    while (arr[right] > pivot)
      right--;
    if (left <= right) {
      std::swap(arr[left], arr[right]);
      left++;
      right--;
    }
  }
  return left;
}

// 选择第k小元素的函数
int select(std::vector<int> &arr, int left, int right, int k) {
  if (left == right)
    return arr[left];

  int pivot = media(arr, left, right);
  int partitionIdx = partition(arr, left, right, pivot);

  int length = partitionIdx - left;
  if (length == k) {
    return arr[partitionIdx - 1]; // 找到第k小元素
  } else if (k < length) {
    return select(arr, left, partitionIdx - 1, k);
  } else {
    return select(arr, partitionIdx, right, k - length);
  }
}

// 主函数
int main() {
  // 0 - 14
  std::vector<int> arr = {9, 3, 4, 8, 7, 2, 6, 5, 1, 0, 10, 14, 12, 11, 13};
  int k = 5;

  int res = select(arr, 0, arr.size() - 1, k);

  std::cout << "第" << k << "小元素是：" << res << std::endl;

  return 0;
}
