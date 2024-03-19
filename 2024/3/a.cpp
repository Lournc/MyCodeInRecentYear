#include <iostream>
#include <map>
#include <vector>
using namespace std;
int main() {
  map<int, vector<pair<int, int>>> mm;
  int s, t, n, m;
  cin >> s >> t >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    mm[a].push_back({b, c});
    mm[b].push_back({a, c});
  }
  return 0;
}