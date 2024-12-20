#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> threeSum(vector<int> &nums) {
  vector<vector<int>> res;
  std::sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); i++) {
    if (i > 0 && nums[i] == nums[i - 1])
      continue; // 跳过重复元素
    int left = i + 1, right = nums.size() - 1;
    while (left < right) {
      int sum = nums[i] + nums[left] + nums[right];
      if (sum == 0) {
        res.push_back({nums[i], nums[left], nums[right]});
        while (left < right && nums[left] == nums[left + 1])
          left++; // 跳过重复元素
        while (left < right && nums[right] == nums[right - 1])
          right--; // 跳过重复元素
        left++;
        right--;
      } else if (sum < 0) {
        left++;
      } else {
        right--;
      }
    }
  }
  return res;
}

int main() {
  vector<int> nums{-4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6};
  auto r = threeSum(nums);
  for (auto &v : r) {
    for (auto vv : v) {
      cout << vv << ' ';
    }
    cout << '\n';
  }
  return 0;
}