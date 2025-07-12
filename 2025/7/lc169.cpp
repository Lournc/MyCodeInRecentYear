#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
public:
  int majorityElement(vector<int> &nums) {
    map<int, int> m;
    for (int &n : nums) {
      m[n]++;
      if (m[n] > nums.size() / 2) {
        return n;
      }
    }
    return 0;
  }
};

int main() {
  vector<int> nums{2, 2, 1, 1, 1, 2, 2};
  Solution s;
  cout << s.majorityElement(nums);
  return 0;
}