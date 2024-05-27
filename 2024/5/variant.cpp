#include <iostream>
#include <variant>
template <typename T> struct variant_base {
  T data;
};

template <typename A, typename... T> class variant {
  union {
    variant_base<A> data;
    variant<T...> data_;
  };

public:
  A get() { return data.data; }
};