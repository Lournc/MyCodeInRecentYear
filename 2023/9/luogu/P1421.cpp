#include <iostream>
int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << int(((double)b / 10 + a) / 1.9);
    return 0;
}