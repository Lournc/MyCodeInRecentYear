#include <iostream>
int main()
{
    int a[8] = {70, 50, 30, 20, 10, 70, 40, 60};
    for (int i = 1; i < 8; i++)
    {
        int b = i;
        for (int j = i - 1; j >= 0; j--)
        {
            if (a[b] < a[j])
                std::swap(a[b--], a[j]);
        }
    }
    for (int i = 0; i < sizeof(a) / sizeof(int); i++)
    {
        std::cout << a[i] << ' ';
    }
    return 0;
}