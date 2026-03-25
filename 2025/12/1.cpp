#include <iostream>

using namespace std;

int GetParentIndex(int node_index) { return (node_index - 1) / 2; }

void BuildHeap(int *arr, int len) {
  for (int i = len - 1; i > 0; i--) {
    int parent_index = GetParentIndex(i);
    int data_index = i;
    while (data_index > 0 && arr[data_index] > arr[parent_index]) {
      std::swap(arr[data_index], arr[parent_index]);
      data_index = parent_index;
      parent_index = GetParentIndex(parent_index);
    }
  }
}

void HeapSort(int *arr, int len) {
  for (int i = len - 1; i > 0; i--) {
    std::swap(arr[i], arr[0]);
    int max_child_index = 1; // 最大子节点索引
    int index = 0;
    while (max_child_index < i) { // 子节点不能是已经排序过的点
      if (max_child_index + 1 < i &&
          arr[max_child_index] < arr[max_child_index + 1]) {
        max_child_index++;
      }
      if (arr[index] > arr[max_child_index]) {
        break;
      }
      swap(arr[index], arr[max_child_index]);
      index = max_child_index;
      max_child_index = max_child_index * 2 + 1;
    }
  }
}

int main() {
  int arr[10] = {3, 10, 8, 7, 9, 56, 2, 13, 89, 25};
  BuildHeap(arr, 10);
  HeapSort(arr, 10);
  for (int &num : arr) {
    cout << num << ' ';
  }
  return 0;
}