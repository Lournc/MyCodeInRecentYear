#pragma once
// 该实现会由于内存对齐导致浪费一些内存，使用下边的宏可以取消内存对齐
#pragma pack(push, 1)
#include <stdexcept>
#include <utility>
namespace koarz {
template <unsigned IDX, typename T> struct tuple_head {
  T data_;
  tuple_head(T data) : data_(data) {}
};

template <unsigned IDX, typename HEAD, typename... TAIL> class tuple_impl {
public:
  using head_t = tuple_head<IDX, HEAD>;
  using tail_t = tuple_impl<IDX + 1, TAIL...>;

private:
  head_t head_;
  tail_t tail_;

public:
  tuple_impl(HEAD head_data) : head_(head_data) {}
  tuple_impl(HEAD head_data, TAIL... tail)
      : head_(head_data), tail_(std::forward<TAIL>(tail)...) {}
  auto get(unsigned p) -> decltype(tail_.get(p)) {
    if (IDX == p) {
      return head_.data_;
    }
    return tail_.get(p);
  }
};
template <unsigned IDX, typename HEAD> class tuple_impl<IDX, HEAD> {
public:
  using head_t = tuple_head<IDX, HEAD>;

private:
  head_t head_;

public:
  tuple_impl(HEAD head) : head_(head) {}
  auto get(unsigned p) {
    if (IDX == p) {
      return head_.data_;
    }
    throw std::runtime_error("look like you input a wrong index\n");
  }
};
template <typename... ARGS> class tuple {
  tuple_impl<0, ARGS...> data_;

public:
  tuple(ARGS... args) : data_(std::forward<ARGS>(args)...) {}
  auto get(unsigned p) { return data_.get(p); };
};
} // namespace koarz
#pragma pack(pop)