
#include <iostream>
#include <tuple>
#include <vector>

std::tuple<int, int, int> fun1(const std::vector<int> &arr, int low, int mid,
                               int high) {
  int left_sum = 1 << 31;
  int sum = 0;
  int max_left = mid;
  for (int i = mid; i >= low; --i) {
    sum += arr[i];
    if (sum > left_sum) {
      left_sum = sum;
      max_left = i;
    }
  }

  int right_sum = 1 << 31;
  sum = 0;
  int max_right = mid + 1;
  for (int j = mid + 1; j <= high; ++j) {
    sum += arr[j];
    if (sum > right_sum) {
      right_sum = sum;
      max_right = j;
    }
  }

  return std::make_tuple(max_left, max_right, left_sum + right_sum);
}

std::tuple<int, int, int> max_subarray(const std::vector<int> &arr, int low,
                                       int high) {
  if (low == high) {
    return std::make_tuple(low, high, arr[low]);
  } else {
    int mid = (low + high) / 2;
    auto left = max_subarray(arr, low, mid);
    auto right = max_subarray(arr, mid + 1, high);
    auto cross = fun1(arr, low, mid, high);

    int left_sum, right_sum, cross_sum;
    std::tie(std::ignore, std::ignore, left_sum) = left;
    std::tie(std::ignore, std::ignore, right_sum) = right;
    std::tie(std::ignore, std::ignore, cross_sum) = cross;

    if (left_sum >= right_sum && left_sum >= cross_sum) {
      return left;
    } else if (right_sum >= left_sum && right_sum >= cross_sum) {
      return right;
    } else {
      return cross;
    }
  }
}

std::tuple<std::vector<int>, int>
find_max_subarray(const std::vector<int> &arr) {
  int low, high, sum;
  std::tie(low, high, sum) = max_subarray(arr, 0, arr.size() - 1);
  std::vector<int> max_sub(arr.begin() + low, arr.begin() + high + 1);
  
  return std::make_tuple(max_sub, sum);
}

int main() {
  std::vector<int> arr = {13, -3, -25, 20, -3,  -16, -23, 18,
                          20, -7, 12,  -5, -22, 15,  -4,  7};
  std::vector<int> max_subarray;
  int max_sum;
  std::tie(max_subarray, max_sum) = find_max_subarray(arr);

  std::cout << "最大子数组是:";
  for (int num : max_subarray) {
    std::cout << " " << num;
  }
  std::cout << "\n最大子数组之和: " << max_sum << std::endl;

  return 0;
}
