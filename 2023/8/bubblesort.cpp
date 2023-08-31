#include <iostream>
#include <utility>
int main()
{
    int a[]{5, 2, 4, 8, 3, 6, 8, 10, 1, 1, 2};
    for (int i = 0; i < sizeof(a) / sizeof(int); i++)
    {
        for (int j = 1; j < sizeof(a) / sizeof(int); j++)
        {
            if (a[j] < a[j - 1])
                std::swap(a[j], a[j - 1]);
        }
    }
    for (int i = 0; i < sizeof(a) / sizeof(int); i++)
    {
        std::cout << a[i] << ' ';
    }
    return 0;
}