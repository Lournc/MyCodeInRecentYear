#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int> &height) {
  int l{}, r{static_cast<int>(height.size() - 1)}, res{};
  while (l < r) {
    int h = min(height[l], height[r]);
    res = max((r - l) * h, res);
    if (h == height[l]) {
      l++;
    } else {
      r--;
    }
  }
  return res;
}

int main() {
  vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
  cout << maxArea(height);
  return 0;
}