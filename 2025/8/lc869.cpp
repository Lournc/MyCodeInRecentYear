#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

class Solution {
public:
  bool reorderedPowerOf2(int n) {
    unordered_map<int, int> t;
    while (n) {
      t[n % 10]++;
      n /= 10;
    }
    for (int i = 0; i < 31; i++) {
      int m = 1 << i;
      unordered_map<int, int> t1;
      while (m) {
        t1[m % 10]++;
        m /= 10;
      }
      if (t1.size() == t.size()) {
        bool f{true};
        for (auto [k, v] : t1) {
          if (t.contains(k)) {
            f &= t[k] == v;
          } else {
            f = false;
            break;
          }
        }
        if (f) {
          return true;
        }
      }
    }
    return false;
  }
};

int main() {
  Solution s;
  cout << s.reorderedPowerOf2(564621);
  return 0;
}