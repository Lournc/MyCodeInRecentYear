#include <cstdint>
#include <iostream>
#include <unordered_map>

class Wrap32 {
public:
  explicit Wrap32(uint32_t raw_value) : raw_value_(raw_value) {}
  bool operator==(const Wrap32 &other) const {
    return raw_value_ == other.raw_value_;
  }

protected:
  uint32_t raw_value_{};
};

struct TCPSenderMessage {
  Wrap32 seqno{0};

  bool SYN{};
  std::string payload{};
  bool FIN{};

  bool RST{};

  size_t sequence_length() const { return SYN + payload.size() + FIN; }
};

template <> struct std::hash<Wrap32> {
  std::size_t operator()(const Wrap32 &s) const noexcept {
    auto *data = reinterpret_cast<const uint32_t *>(&s);
    return std::hash<uint32_t>{}(*data);
  }
};

int main() {
  std::unordered_map<Wrap32, TCPSenderMessage> data_slice_{};
  auto seqno = Wrap32{0};
  data_slice_.emplace(
      seqno,
      TCPSenderMessage{seqno, false, std::string("Hello"), false, false});
  std::cout << data_slice_.size() << '\n';
  data_slice_.erase(seqno);
  std::cout << data_slice_.size() << '\n';
  return 0;
}