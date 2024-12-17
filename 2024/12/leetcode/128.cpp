#include <bits/stdc++.h>

using namespace std;

int longestConsecutive(vector<int> &nums) {
  unordered_set<int> t;
  for (auto n : nums) {
    t.insert(n);
  }
  int res{};
  for (auto v : t) {
    if (t.contains(v - 1)) {
      continue;
    }
    int n{1};
    while (t.contains(v + 1)) {
      n++;
      v++;
    }
    res = max(res, n);
  }
  return res;
}

int main() {
  vector<int> nums{100, 4, 200, 1, 3, 2};
  cout << longestConsecutive(nums);
  return 0;
}