#include <array>
#include <string_view>

template <std::string_view... Parts> struct ConcatStrings {
  static constexpr auto concat() {
    constexpr auto length = (Parts.size() + ... + 0); // 计算总长度
    std::array<char, length + 1> result = {};

    size_t index = 0;
    ((Parts.copy(result.data() + index, Parts.size()), index += Parts.size()),
     ...);

    result[length] = '\0';
    return result;
  }

  static constexpr auto value = concat();
};

// 使用方式
constexpr auto combined_string = ConcatStrings<"Hello, ", "World", "!">::value;

int main() {
  constexpr std::string_view result(combined_string.data());
  static_assert(result == "Hello, World!"); // 编译期检查
}