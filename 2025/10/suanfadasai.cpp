#include <format>
#include <iostream>
#include <string>

using namespace std;

int main() {
  // vmess://5dc94f3a-ecf0-42d8-ae27-722a68a6456c@192.168.0.2:35897?type=tcp&encryption=aes-128-gcm#node123
  string str;
  cin >> str;
  string type, name, server, port, uuid, cipher, network;
  auto a = str.find("://");
  auto b = str.find("@");
  auto c = str.find("?type=");
  auto d = str.find("&encryption=");
  auto e = str.find("#");
  type = str.substr(0, a);
  uuid = str.substr(a + 3, b - a - 3);
  auto p = str.substr(b + 1, c - b - 1);
  if (!p.starts_with("[")) {
    server = p.substr(0, p.find(":"));
    port = p.substr(p.find(":") + 1);
  } else {
    server = p.substr(0, p.find("]:") + 1);
    port = p.substr(p.find("]:") + 2);
  }
  network = str.substr(c + 6, d - c - 6);
  cipher = str.substr(d + 12, e - d - 12);
  name = str.substr(e + 1);
  cout << std::format("name:\"{}\"\ntype:{}\nserver:\"{}\"\nport:{}\nuuid:{}"
                      "\ncipher:{}\nnetwork:{}",
                      name, type, server, port, uuid, cipher, network);
  return 0;
}