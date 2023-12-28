#include <iostream>
#include <utility>
#include <vector>
using namespace std;
int main() {
    int n, c;
    cin >> n >> c;
    vector<int> s(n + 2);
    s[n + 1] = 0b1111111111111111111111111111111;
    int l{}, r{};
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i-1];
    }
    for (;l <= n; l++, r++) {
        while (r <= n && s[r + 1] - s[l] <= c) {
            r++;
        }
    }
    cout << r - l;
    return 0;
}