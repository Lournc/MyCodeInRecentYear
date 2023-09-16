#include <iostream>
int main()
{
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    std::cout << c - a - 1 + (d - b + 60) / 60 << ' ' << (d - b + 60) % 60;
    return 0;
}