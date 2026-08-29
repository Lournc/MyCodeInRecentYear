#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int> &prices) {
  int min_{prices[0]}, res{};
  for (int i = 1; i < prices.size(); i++) {
    res = max(prices[i] - min_, res);
    if (prices[i] < min_) {
      min_ = prices[i];
    }
  }
  return res;
}

int main() {
  vector<int> prices{7, 6, 4, 3, 1};
  cout << maxProfit(prices);
  return 0;
}