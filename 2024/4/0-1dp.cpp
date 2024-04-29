#include <format>
#include <iostream>
constexpr unsigned elem_size = 5;
constexpr unsigned max_bag_size = 13;
int dp[elem_size + 1][max_bag_size + 1];
int b[elem_size + 1][max_bag_size + 1];
void f(int arr[elem_size][2]) {
  for (int i = 1; i <= elem_size; i++) {
    for (int j = 1; j <= max_bag_size; j++) {
      // j还可以代表size
      if (arr[i - 1][1] <= j &&
          (dp[i - 1][j - arr[i - 1][1]] + arr[i - 1][0] > dp[i - 1][j])) {
        dp[i][j] = dp[i - 1][j - arr[i - 1][1]] + arr[i - 1][0];
        b[i][j] = 1;
        continue;
      }
      dp[i][j] = dp[i - 1][j];
    }
  }
}
int main() {
  int v[elem_size][2] = {{24, 10}, {2, 3}, {9, 4}, {10, 5}, {9, 4}};
  f(v);
  std::cout << "决策背包:\n";
  for (int i = 0; i <= elem_size; i++) {
    std::cout << std::format("i={} ", i);
    for (int j = 0; j <= max_bag_size; j++) {
      std::cout << std::format("{:4}", dp[i][j]);
    }
    std::cout << std::endl;
  }
  std::cout << "选择背包:\n";
  for (int i = 0; i <= elem_size; i++) {
    std::cout << std::format("i={} ", i);
    for (int j = 0; j <= max_bag_size; j++) {
      std::cout << std::format("{:4}", b[i][j]);
    }
    std::cout << std::endl;
  }
  return 0;
}