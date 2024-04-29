#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 100010;
int x[N], y[N], ansx, ansy, n;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d %d", &x[i], &y[i]);
  sort(x + 1, x + n + 1);
  sort(y + 1, y + n + 1);
  int mid = y[(n + 1) / 2];
  for (int i = 1; i <= n; i++)
    ansy += abs(y[i] - mid);
  mid = x[(n + 1) / 2];
  int s = mid - n, t = mid + n;
  for (int i = s; i <= t; i++) {
    int sum = 0;
    for (int j = 1; j <= n; j++) {
      int k = x[j];
      sum += abs(k - (i + j - 1));
    }
    if (ansx == 0 || sum < ansx) {
      ansx = sum;
    }
  }
  printf("%d", ansx + ansy);
  return 0;
}