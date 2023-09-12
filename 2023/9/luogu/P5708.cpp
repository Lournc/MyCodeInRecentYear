#include <iostream>
#include <cmath>
int main()
{
    double a, b, c;
    std::cin >> a >> b >> c;
    double p = 0.5 * (a + c + b);
    printf("%.1lf", sqrt(p * (p - a) * (p - b) * (p - c)));
    return 0;
}