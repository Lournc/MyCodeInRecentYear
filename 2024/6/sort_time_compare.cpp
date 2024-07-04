#include <algorithm>
#include <chrono>
#include <climits>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

using namespace std::literals;

void insert_sort(std::vector<std::vector<int>> nums);

void select_sort(std::vector<std::vector<int>> nums);

void heap_sort(std::vector<std::vector<int>> nums);

void merge_sort(std::vector<std::vector<int>> nums);

void quick_sort(std::vector<std::vector<int>> nums);

void standard_sort(std::vector<std::vector<int>> nums);

// 数字规模
int sizes[6]{100, 1000, 2000, 5000, 10000, 100000};

int main() {
  std::vector<std::vector<int>> nums(6, std::vector<int>(0));

  // 生产对应规模随机数字
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT_MIN, INT_MAX);
  for (int i = 0; i < 6; i++) {
    auto &v = nums[i];
    v.resize(sizes[i]);
    for (int j = 0; j < sizes[i]; j++) {
      v[j] = distrib(gen);
    }
  }
  // 调用对应函数，输出排序时间
  insert_sort(nums);
  select_sort(nums);
  heap_sort(nums);
  merge_sort(nums);
  quick_sort(nums);
  standard_sort(nums);
  return 0;
}

void insert_sort(std::vector<std::vector<int>> nums) {
  std::cout << "insert_sort\n";
  for (auto &v : nums) {
    const std::chrono::time_point<std::chrono::steady_clock> start =
        std::chrono::steady_clock::now();
    // 排序主体
    for (int i = 1; i < v.size(); i++) {
      int b = i;
      for (int j = i - 1; j >= 0; j--) {
        if (v[b] < v[j]) {
          std::swap(v[b--], v[j]);
        }
      }
    }

    const auto end = std::chrono::steady_clock::now();
    std::cout << "数据规模：" << v.size() << " 排序花费了 "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
              << " ≈ " << (end - start) / 1ms << "ms\n";
  }
  std::cout << "end\n";
}

void select_sort(std::vector<std::vector<int>> nums) {
  std::cout << "select_sort\n";
  for (auto &v : nums) {
    const std::chrono::time_point<std::chrono::steady_clock> start =
        std::chrono::steady_clock::now();

    // 排序主体
    for (int i = 0; i < v.size() - 1; i++) {
      uint32_t min_idx = i;
      for (int j = i + 1; j < v.size(); j++) {
        if (v[min_idx] > v[j]) {
          min_idx = j;
        }
      }
      std::swap(v[i], v[min_idx]);
      // 这行代码直接调用算法库函数，一行就可以替换上边内容，但是效率太高（可以让该排序速度达到插入排序的1/3），所以不使用
      // std::swap(*std::min_element(&v[i], &v[v.size() - 1]), v[i]);
    }

    const auto end = std::chrono::steady_clock::now();
    std::cout << "数据规模：" << v.size() << " 排序花费了 "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
              << " ≈ " << (end - start) / 1ms << "ms\n";
  }
  std::cout << "end\n";
}

void heap_sort(std::vector<std::vector<int>> nums) {
  std::cout << "heap_sort\n";
  // 下滤函数
  auto UpToDown = [](std::vector<int> &data, uint32_t index, uint32_t size) {
    int maxindex; // maxindex用来储存a[index]的最大子节点
    do // 既然选择执行下滤那么index一定不在最底层，所以至少执行一次下滤
    {
      maxindex = 2 * index;
      if (maxindex + 1 < size && data[maxindex + 1] > data[maxindex])
        maxindex++;
      if (data[index] < data[maxindex])
        std::swap(data[index], data[maxindex]);
      else
        break;
      index = maxindex;
    } while (index < size / 2);
  };
  // 建堆函数
  auto build_heap = [&](std::vector<int> &data) {
    for (int i = data.size() / 2; i > 0; i--) {
      UpToDown(data, i, data.size());
    }
  };

  // 堆排序需要先让索引0为无效元素，也就是所有的元素都应该向后移一位
  std::vector<std::vector<int>> newdata(6, std::vector<int>(0));
  for (int i = 0; i < 6; i++) {
    newdata[i].resize(sizes[i] + 1);
    for (int j = 0; j < sizes[i]; j++) {
      newdata[i][j + 1] = nums[i][j];
    }
  }

  for (auto &v : newdata) {
    const std::chrono::time_point<std::chrono::steady_clock> start =
        std::chrono::steady_clock::now();

    // 需要先建堆，再排序
    build_heap(v);
    for (int i = v.size() - 1; i > 0; i--) {
      std::swap(v[i], v[1]);
      UpToDown(v, 1, i);
    }
    std::swap(v[1], v[2]);

    const auto end = std::chrono::steady_clock::now();
    std::cout << "数据规模：" << v.size() - 1 << " 排序花费了 "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
              << " ≈ " << (end - start) / 1ms << "ms\n";
  }
  std::cout << "end\n";
}

// 合并两个已排序的vector
void merge(std::vector<int> &arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<int> l(n1), r(n2);
  for (int i = 0; i < n1; i++)
    l[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    r[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (l[i] <= r[j]) {
      arr[k] = l[i];
      i++;
    } else {
      arr[k] = r[j];
      j++;
    }
    k++;
  }

  if (i < n1) {
    memmove(&arr[k], &l[i], (n1 - i) * sizeof(int));
  }
  if (j < n2) {
    memmove(&arr[k], &r[j], (n2 - j) * sizeof(int));
  }
}

void mergesort(std::vector<int> &arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void merge_sort(std::vector<std::vector<int>> nums) {
  std::cout << "merge_sort\n";
  for (auto &v : nums) {
    const std::chrono::time_point<std::chrono::steady_clock> start =
        std::chrono::steady_clock::now();

    mergesort(v, 0, v.size() - 1);

    const auto end = std::chrono::steady_clock::now();
    std::cout << "数据规模：" << v.size() << " 排序花费了 "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
              << " ≈ " << (end - start) / 1ms << "ms\n";
  }
  std::cout << "end\n";
}

void quicksort(std::vector<int> &arr, int l, int r) {
  if (l >= r) {
    return;
  }
  int i{l}, j{l};
  while (j < r) {
    if (arr.at(j) <= arr.at(r)) {
      if (i != j) {
        std::swap(arr.at(j), arr.at(i));
      }
      i++;
    }
    j++;
  }
  std::swap(arr.at(i), arr.at(j));
  quicksort(arr, l, i - 1);
  quicksort(arr, i + 1, r);
}

void quick_sort(std::vector<std::vector<int>> nums) {
  std::cout << "quick_sort\n";
  for (auto &v : nums) {
    const std::chrono::time_point<std::chrono::steady_clock> start =
        std::chrono::steady_clock::now();

    quicksort(v, 0, v.size() - 1);

    const auto end = std::chrono::steady_clock::now();
    std::cout << "数据规模：" << v.size() << " 排序花费了 "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
              << " ≈ " << (end - start) / 1ms << "ms\n";
  }
  std::cout << "end\n";
}

void standard_sort(std::vector<std::vector<int>> nums) {
  std::cout << "standard_library_sort\n";
  for (auto &v : nums) {
    const std::chrono::time_point<std::chrono::steady_clock> start =
        std::chrono::steady_clock::now();

    std::sort(v.begin(), v.end());

    const auto end = std::chrono::steady_clock::now();
    std::cout << "数据规模：" << v.size() << " 排序花费了 "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
              << " ≈ " << (end - start) / 1ms << "ms\n";
  }
  std::cout << "end\n";
}