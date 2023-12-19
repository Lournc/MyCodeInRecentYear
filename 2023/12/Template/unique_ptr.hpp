#pragma once

#include <algorithm>
#include <iostream>

namespace koarz{

template <typename T>
class unique_ptr;

} // namespace koarz

template <typename T>
class koarz::unique_ptr {
private:
    T* ptr_;
public:
    unique_ptr() : ptr_(nullptr){};
    unique_ptr(T* ptr) : ptr_(ptr){};
    unique_ptr(koarz::unique_ptr<T>&) = delete;
    unique_ptr& operator=(koarz::unique_ptr<T>&) = delete;
    unique_ptr(koarz::unique_ptr<T>&&) noexcept;
    unique_ptr& operator=(koarz::unique_ptr<T>&&) noexcept;
    T* operator->() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* get() const { return ptr_; }
    T* release() { T* tmp = ptr_; ptr_ = nullptr; return tmp; }
    void reset(T *ptr = nullptr) { delete ptr_; ptr_ = ptr; }
    void swap(koarz::unique_ptr<T>&);
    ~unique_ptr() { delete ptr_; }
};

template <typename T>
koarz::unique_ptr<T>::unique_ptr(koarz::unique_ptr<T>&& other) noexcept {
    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
}

template <typename T>
koarz::unique_ptr<T>& koarz::unique_ptr<T>::operator=(koarz::unique_ptr<T>&& other) noexcept {
    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
}