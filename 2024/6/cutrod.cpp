#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

// 函数声明：计算最大销售收益
int cutRod(const std::vector<int> &price, int n);

int main() {
  std::vector<int> price = {
      0,  1,  5,  8,  9, 10,
      17, 17, 20, 24, 24}; // 价格表，price[i] 表示长度为 i 的钢条价格
  int n = 10;              // 钢条长度

  int res = cutRod(price, n);
  std::cout << "最大销售收益是 " << res << std::endl;

  return 0;
}

// 函数定义：计算最大销售收益
int cutRod(const std::vector<int> &price, int n) {
  std::vector<int> dp(n + 1, 0); // dp[i] 表示长度为 i 的钢条的最大收益

  // 填充 dp 数组
  for (int i = 1; i <= n; ++i) {
    int max_val = INT_MIN;
    for (int j = 1; j <= i; ++j) {
      max_val = std::max(max_val, price[j] + dp[i - j]);
    }
    dp[i] = max_val;
  }

  return dp[n];
}