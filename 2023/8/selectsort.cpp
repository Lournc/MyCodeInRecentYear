#include <iostream>
#include <utility>
int main()
{
    int arr[]{5, 8, 1, 4, 6, 5, 7, 1, 33, 4};
    for (int i = 0; i < sizeof(arr) / sizeof(int) - 1; i++)
    {
        int min{i};
        for (int j = i; j < sizeof(arr) / sizeof(int); j++)
        {
            min = arr[min] > arr[j] ? j : min;
        }
        std::swap(arr[min], arr[i]);
    }
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        std::cout << arr[i] << ' ';
    }
    return 0;
}