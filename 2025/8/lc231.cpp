#include <iostream>

using namespace std;

class Solution {
public:
  bool isPowerOfTwo(int n) {
    for (int i = 0; i < 31; i++) {
      if (n == 1 << i)
        return true;
    }
    return false;
  }
};

int main() {
  Solution s;
  cout << s.isPowerOfTwo(1 << 20);
  return 0;
}