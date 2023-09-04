#include <iostream>
void heapsort(int a[], size_t size)
{
}
int main()
{
    int a[8] = {70, 50, 30, 20, 10, 70, 40, 60};
    heapsort(a, 8);
    for (int i = 0; i < 8; i++)
        std::cout << a[i] << ' ';
}