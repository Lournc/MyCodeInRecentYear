#include <iostream>
#include <cmath>
int main()
{
    double s, v;
    std::cin >> s >> v;
    int t = ceil(s / v) + 10;
    int h = t / 60;
    if (t >= 60)
    {
        t %= 60;
    }
    if (h > 7)
    {
        h -= 24;
    }
    printf("%02d:%02d", 7 - h, 60 - t);
    return 0;
}