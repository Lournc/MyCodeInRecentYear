#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define ALWAYS_INLINE __attribute__((always_inline))
struct StringRef {
  const char *data = nullptr;
  size_t size = 0;

  StringRef() = default;
  StringRef(const char *data_, size_t size_) : data(data_), size(size_) {}
  ~StringRef() = default;
  std::string to_string() const { return std::string(data, size); };
};

struct ColumnString {
  using Offsets = std::vector<int>;
  using Chars = std::vector<char>;

  Offsets offsets;

  Chars chars;

  Chars &get_chars() { return chars; }
  Offsets &get_offsets() { return offsets; }

  void insert_data(const char *pos, size_t length) {
    const size_t old_size = chars.size();
    const size_t new_size = old_size + length;

    if (length) {
      chars.resize(new_size);
      memcpy(chars.data() + old_size, pos, length);
    }
    offsets.push_back(new_size);
  }

  size_t ALWAYS_INLINE offset_at(ssize_t i) const { return offsets[i - 1]; }
  size_t ALWAYS_INLINE size_at(ssize_t i) const {
    return offsets[i] - offsets[i - 1];
  }
  size_t size() const { return offsets.size(); }
  StringRef get_data_at(size_t n) const {
    return StringRef(&chars[offset_at(n)], size_at(n));
  }
};
template <typename T> struct ColumnVector {
  using value_type = T;
  ColumnVector() = default;
  ColumnVector(const size_t n) : data(n) {}
  ColumnVector(const size_t n, const value_type x) : data(n, x) {}
  value_type operator[](size_t n) const { return data[n]; }
  std::vector<value_type> data;
};

unsigned int index_check_const(unsigned int arg, bool constancy) noexcept {
  return constancy ? 0 : arg;
}
using Int32 = int32_t;

std::pair<bool, size_t> get_size(size_t &str_size, int &pos, int &len,
                                 size_t &ins_size) {
  if (pos > str_size || pos < 1) {
    return {true, str_size};
  }
  if (len < 0 || pos + len - 1 >= str_size) {
    len = str_size - pos + 1;
    return {false, pos + ins_size - 1};
  }
  return {false, str_size - len + ins_size};
}
template <bool is_const>
void f(const ColumnString *col_origin, const ColumnVector<int> *col_pos,
       const ColumnVector<int> *col_len, const ColumnString *col_insert,
       ColumnString *col_res, bool col_const[4]) {
  size_t input_rows_count{2};

  auto &col_res_chars = col_res->get_chars();
  auto &col_res_offsets = col_res->get_offsets();

  if constexpr (is_const) {
    StringRef origin_str = col_origin->get_data_at(0);
    StringRef insert_str = col_insert->get_data_at(0);
    auto pos = col_pos->data[0];
    auto len = col_len->data[0];
    if (pos < 1) {
      if (col_const[0]) {
        for (size_t i = 0; i < input_rows_count; i++) {
          col_res->insert_data(origin_str.data, origin_str.size);
        }
      } else {
        for (size_t i = 0; i < input_rows_count; i++) {
          origin_str = col_origin->get_data_at(i);
          col_res->insert_data(origin_str.data, origin_str.size);
        }
      }
      return;
    }
  }
  for (size_t i = 0; i < input_rows_count; i++) {
    StringRef origin_str =
        col_origin->get_data_at(index_check_const(i, col_const[0]));
    auto pos = col_pos->operator[](index_check_const(i, col_const[1]));
    auto len = col_len->operator[](index_check_const(i, col_const[2]));
    StringRef insert_str =
        col_insert->get_data_at(index_check_const(i, col_const[3]));
    if (auto [is_origin, offset] =
            get_size(origin_str.size, pos, len, insert_str.size);
        is_origin) {
      ;
    } else {
      const auto old_size = col_res_chars.size();
      col_res_chars.resize(old_size + offset);
      memcpy(col_res_chars.data() + old_size, origin_str.data, pos - 1);
      memcpy(col_res_chars.data() + old_size + pos - 1, insert_str.data,
             insert_str.size);
      memcpy(col_res_chars.data() + old_size + pos - 1 + insert_str.size,
             origin_str.data + pos + len - 1, origin_str.size - pos - len + 1);
      col_res_offsets.push_back(offset + old_size);
    }
  }
}

int main() {
  ColumnString col_origin;
  ColumnVector<int> col_pos;
  ColumnVector<int> col_len;
  ColumnString col_insert;
  ColumnString col_res;
  col_origin.chars.push_back('H');
  col_origin.chars.push_back('e');
  col_origin.chars.push_back('l');
  col_origin.chars.push_back('l');
  col_origin.chars.push_back('o');
  col_origin.chars.push_back(' ');
  col_origin.chars.push_back('W');
  col_origin.chars.push_back('o');
  col_origin.chars.push_back('r');
  col_origin.chars.push_back('l');
  col_origin.chars.push_back('d');
  col_origin.offsets.push_back(11);
  col_origin.chars.push_back('W');
  col_origin.chars.push_back('o');
  col_origin.chars.push_back('r');
  col_origin.chars.push_back('l');
  col_origin.chars.push_back('d');
  col_origin.offsets.push_back(16);
  col_pos.data.push_back(0);
  col_len.data.push_back(5);
  col_insert.chars.push_back('D');
  col_insert.chars.push_back('o');
  col_insert.chars.push_back('r');
  col_insert.chars.push_back('i');
  col_insert.chars.push_back('s');
  col_insert.offsets.push_back(5);
  bool is_const[]{0, 1, 1, 1};
  f<true>(&col_origin, &col_pos, &col_len, &col_insert, &col_res, is_const);
  is_const[1] = 0;
  col_pos.data.push_back(2);
  f<false>(&col_origin, &col_pos, &col_len, &col_insert, &col_res, is_const);
  for (auto &v : col_res.chars) {
    std::cout << v;
  }
}