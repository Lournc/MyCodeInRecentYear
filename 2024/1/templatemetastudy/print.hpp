#pragma once
#include <format>
#include <iostream>
#include <string_view>
namespace koarz {

template <typename... T> void print(std::string_view fmt, T... v) {
  std::cout << std::vformat(fmt, std::make_format_args(v...));
}

} // namespace koarz
