#include <iostream>
#include <algorithm>
using namespace std;

void UpToDown(int a[], unsigned int index, size_t size) // 下滤
{
    int maxindex; // maxindex用来储存a[index]的最大子节点
    do            // 既然选择执行下滤那么index一定不在最底层，所以至少执行一次下滤
    {
        maxindex = 2 * index;
        if (maxindex + 1 < size && a[maxindex + 1] > a[maxindex]) // 首先得保证读数据不会内存溢出吧
            maxindex++;
        if (a[index] < a[maxindex])
            swap(a[index], a[maxindex]);
        else
            break;
        index = maxindex;
    } while (index < size / 2);
}

void DownToUp(int a[], unsigned int index) // 上滤
{
    int faindex = index / 2;
    do
    {
        if (a[index] > a[faindex])
            swap(a[index], a[faindex]);
        else
            break;
        index /= 2;
        faindex = index / 2;
    } while (faindex > 0);
}
void BuildHeap(int a[], size_t size) // 自顶而下建堆法
{
    if (size < 3)
        return;
    for (int i = 2; i < size; i++)
    {
        DownToUp(a, i);
    }
}
// void BuildHeap(int a[], size_t size) // 自下而上建堆法
// {
//     for (int i = size / 2; i > 0; i--)
//     {
//         UpToDown(a, i, size);
//     }
// }
void HeapSort(int a[], size_t size)
{
    for (int i = size - 1; i > 0; i--)
    {
        swap(a[i], a[1]);
        UpToDown(a, 1, i);
    }
    swap(a[1], a[2]);
}
int main()
{
    int a[9] = {0, 3, 5, 4, 1, 2, 0, 85, 7};
    // HeapSort(a, 8);
    BuildHeap(a, 9);
    for (int i = 1; i < 9; i++)
        cout << a[i] << ' ';
    cout << endl;
    HeapSort(a, 9);
    for (int i = 1; i < 9; i++)
        cout << a[i] << ' ';
}