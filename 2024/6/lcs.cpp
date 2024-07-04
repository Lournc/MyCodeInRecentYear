#include <iostream>
#include <string>
#include <vector>
using namespace std;

pair<int, string> LCS(string X, string Y) {
  int m = X.length();
  int n = Y.length();

  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (X[i - 1] == Y[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  int lengthLCS = dp[m][n];

  int i = m, j = n;
  string lcs;

  while (i > 0 && j > 0) {
    if (X[i - 1] == Y[j - 1]) {
      lcs = X[i - 1] + lcs;
      i--;
      j--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }

  return {lengthLCS, lcs};
}

int main() {
  string X = "ABCBDAB";
  string Y = "BDCAB";

  auto result = LCS(X, Y);
  int lengthLCS = result.first;
  string lcs = result.second;

  cout << "最长公共子序列长度: " << lengthLCS << endl;
  cout << "最长公共子序列: " << lcs << endl;

  return 0;
}
