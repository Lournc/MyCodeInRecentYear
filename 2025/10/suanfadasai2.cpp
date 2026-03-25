#include <algorithm>
#include <iostream>
#include <set>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

// <x, y>, r
vector<pair<pair<int, int>, int>> dat;

int dfs(int i, set<int> &yizha, int n) {
  int mm{};
  auto p = dat[i].first;
  auto r = dat[i].second;
  for (int j = 0; j < n; j++) {
    auto p2 = dat[j].first;
    if (yizha.contains(j)) {
      continue;
    }
    int x1 = p.first, x2 = p2.first, y1 = p.second, y2 = p2.second;
    if ((x2 - x1) * (x2 - x1) + (y1 - y2) * (y1 - y2) <= r * r) {
      mm++;
      yizha.insert(j);
      mm += dfs(j, yizha, n);
    }
  }
  return mm;
}

int main() {
  int n;
  cin >> n;
  dat.resize(n);
  for (int i = 0; i < n; i++) {
    int x, y, r;
    cin >> x >> y >> r;
    dat[i] = make_pair(make_pair(x, y), r);
  }
  int res{};
  for (int i = 0; i < n; i++) {
    set<int> yizha;
    int mm = dfs(i, yizha, n);
    if (mm > res)
      res = mm;
  }
  cout << res;
  return 0;
}