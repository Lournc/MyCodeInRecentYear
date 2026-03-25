#include <iostream>
#include <vector>

using namespace std;

int main() {
  double A, B, C;
  cin >> A >> B >> C;
  vector<int> res;
  for (int i = 1; i < 2001; i++) {
    int sum = A * i;
    vector<int> arr(i);
    if (i & 1) {
      arr[(i + 1) / 2] = B;
    }
  }
  cout << res.size();
  for (int n : res) {
    cout << n << ' ';
  }
  return 0;
}