#include <iostream>
#include <utility>
#include <vector>
template <typename T>
void quicksort(T *begin, T *end)
{
    if (begin >= end)
        return;
    unsigned left = 0, right = end - begin, mid = right / 2;
    int l = left;
    int r = right;
    int v = begin[mid];
    while (l < r)
    {
        while (begin[l] < v)
            l++;
        while (begin[r] > v)
            r--;
        if (l < r)
        {
            std::swap(begin[l], begin[r]);
            if (begin[l] == v)
                r--;
            if (begin[r] == v)
                l++;
        }
    }
    if (left < r)
        quicksort(begin, &begin[l - 1]);
    if (l < right)
        quicksort(&begin[left + 1], end);
}

int main()
{
    int a[]{5, 4, 9, 32, 12, 3, 20, 14, 54, 77, 3, 6, 5};
    quicksort(&a[0], &a[12]);
    for (int v : a)
    {
        std::cout << v << ' ';
    }
}