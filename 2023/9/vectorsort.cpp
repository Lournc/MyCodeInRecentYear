#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
int main()
{
    vector<pair<int, int>> a;
    for (int i = 0; i < 5; i++) // 这里写入数据
    {
        int b, c;
        cin >> b >> c;
        a.push_back({b, c});
    }
    sort(a.begin(), a.end(), [](auto a, auto b)
         { return a.first < b.first ? 0 : 1; });
    for (int i = 0; i < 5; i++)
    {
        cout << a[i].first << ' ' << a[i].second << endl;
    }
    return 0;
}