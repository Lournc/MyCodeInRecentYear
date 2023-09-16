#include <iostream>
#include <map>

using namespace std;

map<pair<int, int>, char> mapp;

void drew(int, int, int);

int main()
{
    int m, n, x, y, size;
    cin >> m >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y >> size;
        drew(x, y, size);
    }
    for (int i = 0; i < 2 * m; i++) // 最后画边框
    {
        mapp[{0, i}] = mapp[{m - 1, i}] = '-';
        if (i > 0 && i < m - 1)
            mapp[{i, 0}] = mapp[{i, 2 * m - 1}] = '|';
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 2 * m; j++)
            if (mapp[{i, j}] != 0)
                cout << mapp[{i, j}];
            else
                cout << ' ';
        cout << endl;
    }

    return 0;
}

void drew(int x, int y, int size)
{
    for (int i = x - size; i <= x + size; i++)
    {
        for (int j = y - size; j <= y + size; j++)
        {
            if (abs(i - x) + abs(j - y) < size)
                mapp[{i, j}] = '*';
        }
    }
}