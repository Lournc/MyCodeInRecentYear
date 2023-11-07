#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int findp(string &s)
{
    int p = 0;
    for (; p < s.size() - 1; p++)
    {
        if (p == s.size() - 2)
        {
            return (s[p] < s[p + 1] ? p + 1 : p);
        }
        if (s[p] > s[p + 1])
            break;
    }
    return p;
}
int main()
{
    string str;
    int n;
    cin >> str >> n;
    int len = str.size();
    string ans = str.substr(0, len - n);
    for (int i = len - n; i < len; i++)
    {
        if (ans < ans.substr(0, findp(ans)) + ans.substr(findp(ans) + 1, ans.size()) + str[i])
            continue;
        ans.erase(findp(ans), 1);
        ans += str[i];
    }
    while (ans[0] == '0' && ans.size() > 1)
    {
        ans.erase(0, 1);
    }
    cout << ans;
    return 0;
}