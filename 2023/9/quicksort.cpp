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
    int a[]{11,5,8,30,15,45,22,11,44,33,84,12,23};
    quicksort(&a[0], &a[12]);
    for (int v : a)
    {
        std::cout << v << ' ';
    }
}