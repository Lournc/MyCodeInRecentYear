#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

pair<int, int> func(vector<int> &nums) {
  int n = nums.size();
  if (n == 0)
    return make_pair(-1, -1);

  // 定义一个数组 dp，dp[i] 表示以 nums[i] 结尾的最大子数组和
  vector<int> dp(n);

  // 初始化
  dp[0] = nums[0];
  int max = dp[0];
  int start = 0, end = 0;

  // 状态转移方程：dp[i] = max(dp[i-1] + nums[i], nums[i])
  for (int i = 1; i < n; ++i) {
    if (dp[i - 1] + nums[i] > nums[i]) {
      dp[i] = dp[i - 1] + nums[i];
    } else {
      dp[i] = nums[i];
      start = i;
    }
    if (dp[i] > max) {
      max = dp[i];
      end = i;
    }
  }

  return make_pair(start, end);
}

int main() {
  vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  auto indices = func(nums);
  int start = indices.first;
  int end = indices.second;

  cout << "最大子数组: ";
  for (int i = start; i <= end; ++i) {
    cout << nums[i] << " ";
  }
  cout << endl;

  return 0;
}
