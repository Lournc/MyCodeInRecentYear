#include <iostream>
int main()
{
    int m, t, s;
    std::cin >> m >> t >> s;
    if (t && (m * t - s) > 0)
        std::cout << (m * t - s) / t;
    else
        puts("0");
}