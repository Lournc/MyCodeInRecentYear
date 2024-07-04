#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 函数声明：计算最小编辑距离
int minEditDistance(const std::string &word1, const std::string &word2);

int main() {
  std::string word1 = "kitten";
  std::string word2 = "sitting";

  int distance = minEditDistance(word1, word2);
  std::cout << "\"" << word1 << "\" 和 \"" << word2 << "\" 的最小编辑距离是 "
            << distance << std::endl;

  return 0;
}

// 函数定义：计算最小编辑距离
int minEditDistance(const std::string &word1, const std::string &word2) {
  int m = word1.size();
  int n = word2.size();

  // 创建一个二维数组，dp[i][j]代表word1[0..i-1]和word2[0..j-1]之间的最小编辑距离
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

  // 初始化第一列
  for (int i = 1; i <= m; ++i) {
    dp[i][0] = i; // 从word1[0..i-1]变成空字符串需要的删除操作数
  }

  // 初始化第一行
  for (int j = 1; j <= n; ++j) {
    dp[0][j] = j; // 从空字符串变成word2[0..j-1]需要的插入操作数
  }

  // 填充dp数组
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1]; // 字符相同，不需要额外操作
      } else {
        int insertOp = dp[i][j - 1] + 1;      // 插入操作
        int deleteOp = dp[i - 1][j] + 1;      // 删除操作
        int replaceOp = dp[i - 1][j - 1] + 1; // 替换操作
        dp[i][j] = std::min({insertOp, deleteOp, replaceOp});
      }
    }
  }

  return dp[m][n]; // 返回结果
}