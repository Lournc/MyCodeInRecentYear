#pragma once
namespace koarz {

struct true_type {
  constexpr static bool value{true};
};

struct false_type {
  constexpr static bool value{false};
};

template <typename T, typename U> struct is_same_v : false_type {};

template <typename T> struct is_same_v<T, T> : true_type {};

} // namespace koarz