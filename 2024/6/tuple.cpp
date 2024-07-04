#include <cassert>
#include <format>
#include <iostream>
#include <ostream>
#include <stdexcept>

using uint = unsigned int;
template <uint Index, typename T, typename... Args> struct TupleBasic {
  TupleBasic<Index, T> head_;
  TupleBasic<Index + 1, Args...> tail_;

  TupleBasic(T data, Args... args) : head_(data), tail_(args...) {}
  TupleBasic(TupleBasic<Index, T, Args...> &other)
      : head_(other.head_), tail_(other.tail_) {}

  TupleBasic<Index, T, Args...> &
  operator=(TupleBasic<Index, T, Args...> &other) {
    head_ = other.head_;
    tail_ = other.tail_;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  TupleBasic<Index, T, Args...> tuple) {
    os << tuple.head_ << tuple.tail_;
    return os;
  }

  template <typename _Tp> void read(uint index, _Tp &v) {
    if (index == Index) {
      head_.read(index, v);
      return;
    }
    tail_.read(index, v);
  }

  template <typename _Tp> void write(uint index, _Tp data) {
    if (index == Index) {
      head_.write(index, data);
    } else {
      tail_.write(index, data);
    }
  }
};

template <uint Index, typename T> struct TupleBasic<Index, T> {
  T data_;

  TupleBasic(T data) : data_(data) {}
  TupleBasic(TupleBasic<Index, T> &other) : data_(other.data_) {}

  TupleBasic<Index, T> &operator=(TupleBasic<Index, T> &other) {
    data_ = other.data_;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  TupleBasic<Index, T> tuple) {
    os << tuple.data_ << ' ';
    return os;
  }

  template <typename _Tp> void read(uint index, _Tp &v) {
    if (index == Index) {
      data_.read(v);
      return;
    }
    throw std::overflow_error(std::format(
        "Get index: {} is over the tuple max index: {}", index, Index));
  }

  template <typename _Tp> void write(uint index, _Tp data) {
    data_.write(data);
  }
};

template <typename... Args> class Tuple {
  TupleBasic<0, Args...> tuple_;

public:
  Tuple(Args... args) : tuple_(args...) {}

  Tuple(Tuple<Args...> &other) : tuple_(other.tuple_) {}

  Tuple<Args...> &operator=(Tuple<Args...> &other) {
    tuple_.operator=(other.tuple_);
    return *this;
  }

  template <typename _Tp> void read(uint index, _Tp &v) {
    tuple_.read(index, v);
  }

  template <typename _Tp> void write(uint index, _Tp data) {
    tuple_.write(index, data);
  }

  friend std::ostream &operator<<(std::ostream &os, Tuple<Args...> tuple) {
    os << tuple.tuple_;
    return os;
  }
};

int main() {
  Tuple<int, double, std::string> t{1214, 3.14159, std::string("A")};
  auto t2 = t;
  std::cout << t2;
}