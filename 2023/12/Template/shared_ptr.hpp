#pragma once

#include <atomic>
#include <iostream>

namespace koarz {

template <typename T> class shared_ptr;
} // namespace koarz

template <typename T> class koarz::shared_ptr {
private:
  T *ptr_{nullptr};
  std::atomic_uint *count_{nullptr};
  void release() {
    if (count_ != nullptr) {
      (*count_)--;
      if (*count_ == 0) {
        delete count_;
        delete ptr_;
        count_ = nullptr;
        ptr_ = nullptr;
      }
    }
  }

public:
  shared_ptr() : ptr_(nullptr), count_(nullptr){};
  shared_ptr(T *ptr) : ptr_(ptr) { count_ = new std::atomic_uint(1); };
  shared_ptr(const koarz::shared_ptr<T> &) noexcept;
  shared_ptr &operator=(const koarz::shared_ptr<T> &) noexcept;
  shared_ptr(koarz::shared_ptr<T> &&) noexcept;
  shared_ptr &operator=(koarz::shared_ptr<T> &&) noexcept;
  T *operator->() const { return ptr_; }
  T &operator*() const { return *ptr_; }
  T *get() const { return ptr_; }

  void reset(T *ptr = nullptr) {
    if (ptr == ptr_ || ptr == nullptr)
      return;
    ptr_ = ptr;
    if (count_ != nullptr) {
      *count_ = 1;
    } else {
      count_ = new std::atomic_uint(1);
    }
  }
  void swap(koarz::shared_ptr<T> &);
  int get_count() { return *count_; }
  ~shared_ptr();
};

template <typename T>
koarz::shared_ptr<T>::shared_ptr(const koarz::shared_ptr<T> &other) noexcept {
  if (other.ptr_ != this->ptr_) {
    release();
    ptr_ = other.ptr_;
    count_ = other.count_;
    (*count_)++;
  }
}

template <typename T>
koarz::shared_ptr<T> &
koarz::shared_ptr<T>::operator=(const koarz::shared_ptr<T> &other) noexcept {
  if (other.ptr_ != this->ptr_) {
    release();
    ptr_ = other.ptr_;
    count_ = other.count_;
    (*count_)++;
  }
  return *this;
}

template <typename T>
koarz::shared_ptr<T>::shared_ptr(koarz::shared_ptr<T> &&other) noexcept {
  if (other.ptr_ != this->ptr_) {
    release();
    ptr_ = other.ptr_;
    count_ = other.count_;
  }
}

template <typename T>
koarz::shared_ptr<T> &
koarz::shared_ptr<T>::operator=(koarz::shared_ptr<T> &&other) noexcept {
  if (other.ptr_ != this->ptr_) {
    release();
    ptr_ = other.ptr_;
    count_ = other.count_;
  }
  return *this;
}

template <typename T> koarz::shared_ptr<T>::~shared_ptr() {
  if (count_ != nullptr) {
    (*count_)--;
    if (*count_ == 0) {
      delete ptr_;
      delete count_;
    }
  }
}