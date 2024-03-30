#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
  int coinChange(vector<int> &coins, int amount) {
    if (amount <= 0) {
      return 0;
    }
    // 数组pd储存计算过的最小数量
    int *dp = (int *)calloc(amount + 1, sizeof(int));
    return F(coins, dp, amount);
  }

  // 计算最小硬币数量
  int F(vector<int> &coins, int *dp, int s, int *nums = nullptr) {
    int size = coins.size();
    bool flag{false};
    // 单次循环中硬币数量为nums，不能用该硬币凑为-1，能凑为+1
    if (!nums) {
      nums = (int *)calloc(size, sizeof(int));
      flag = true;
    }

    // 计算选择不同硬币的数量
    for (int i = 0; i < size; i++) {
      if (s - coins[i] < 0)
        nums[i] = -1;
      if (s - coins[i] == 0)
        nums[i] = 1;
      else if (dp[s - coins[i]] != 0)
        nums[i] = dp[s - coins[i]];
      else
        nums[i] = F(coins, dp, s - coins[i], nums);
    }
    // 最小数量
    for (int i = 0; i < size; i++) {
      if (nums[i] > 0)
        nums[0] = (nums[0] < nums[i]) ? nums[0] : nums[i];
    }

    // 该次循环全返回-1
    if (nums[0] == -1)
      return -1;
    else
      dp[s] = nums[0];
    if (flag)
      free(nums);
    // 返回总共s的最小数量赢币
    return dp[s];
  }
};

int main() {
  vector<int> a{1, 2, 5};
  Solution b;
  cout << b.coinChange(a, 11);
  return 0;
}