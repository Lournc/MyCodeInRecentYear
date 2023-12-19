// multi_threaded_sort.h
// #ifndef MULTI_THREADED_SORT_H
// #define MULTI_THREADED_SORT_H

#include <algorithm>
#include <future>
#include <limits>
#include <thread>
#include <type_traits>

template <typename IntegerType>
void multi_threaded_sort(IntegerType *in_data, size_t data_len,
                         size_t thread_num) {
  // compile time type check
  static_assert(std::is_integral<IntegerType>::value,
                "Data type must be integer");

  // under such conditions, multi-thread makes no sense
  // call std::sort directly
  if (data_len <= 1 || thread_num == 0 ||
      data_len < (thread_num + 1) * (thread_num + 1)) {
    std::sort(in_data, in_data + data_len);
    return;
  }

  /* one thread sort one chunk
   * main thread sort the last chunk */
  size_t chunk_size = data_len / (thread_num + 1);
  if (data_len % (thread_num + 1) != 0)
    ++chunk_size;

  // for threads synchronize
  auto sort_promise = new std::promise<void>[thread_num];
  auto sort_future = new std::future<void>[thread_num];
  for (int i = 0; i < thread_num; ++i)
    sort_future[i] = sort_promise[i].get_future();

  // create threads
  for (size_t i = 0; i < thread_num; ++i) {
    std::thread th([=] {
      std::sort(in_data + i * chunk_size, in_data + (i + 1) * chunk_size);
      sort_promise[i].set_value();
    });
    th.detach();
  }

  // sort the last chunk
  std::sort(in_data + chunk_size * thread_num, in_data + data_len);

  // before wait and block, do things not based on data
  auto out_data = new IntegerType[data_len];
  auto index = new size_t[thread_num + 1];
  for (int i = 0; i < thread_num + 1; ++i)
    index[i] = i * chunk_size;

  // wait for all threads
  for (size_t i = 0; i < thread_num; ++i)
    sort_future[i].wait();

  delete[] sort_future;
  delete[] sort_promise;

  // do merge sort
  for (size_t i = 0; i < data_len; ++i) {
    IntegerType min_index;
    IntegerType min_num = std::numeric_limits<IntegerType>::max();

    // traverse every chunk and find the minimum
    for (size_t j = 0; j < thread_num; ++j) {
      if ((index[j] < (j + 1) * chunk_size) && (in_data[index[j]] < min_num)) {
        min_index = j;
        min_num = in_data[index[j]];
      }
    }
    if (index[thread_num] < data_len &&
        (in_data[index[thread_num]] < min_num)) {
      min_index = thread_num;
    }

    out_data[i] = in_data[index[min_index]];
    index[min_index]++;
  }

  std::copy(out_data, out_data + data_len, in_data);
  delete[] out_data;
}

// #endif //MULTI_THREADED_SORT_H
