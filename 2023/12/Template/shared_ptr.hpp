#pragma once

#include <iostream>
#include <atomic>

namespace koarz{

template <typename T>
class shared_ptr;

} // namespace koarz

template <typename T>
class koarz::shared_ptr {
private:
    T* ptr_;
    std::atomic_uint* count;
public:
    shared_ptr() : ptr_(nullptr), count(nullptr) {};
    shared_ptr(T* ptr) : ptr_(ptr) {};
    shared_ptr(koarz::shared_ptr<T>&) = delete;
    shared_ptr& operator=(koarz::shared_ptr<T>&) = delete;
    shared_ptr(koarz::shared_ptr<T>&&) noexcept;
    shared_ptr& operator=(koarz::shared_ptr<T>&&) noexcept;
    T* operator->() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* get() const { return ptr_; }
    T* release() { T* tmp = ptr_; ptr_ = nullptr; return tmp; }
    void reset(T *ptr = nullptr) { delete ptr_; ptr_ = ptr; }
    void swap(koarz::shared_ptr<T>&);
    ~shared_ptr() { delete ptr_; }
};

template <typename T>
koarz::shared_ptr<T>::shared_ptr(koarz::shared_ptr<T>&& other) noexcept {
    if (other.ptr_ != this->ptr_) {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
}

template <typename T>
koarz::shared_ptr<T>& koarz::shared_ptr<T>::operator=(koarz::shared_ptr<T>&& other) noexcept {
    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
}