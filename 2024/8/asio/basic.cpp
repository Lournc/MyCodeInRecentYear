#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

int main() {
  io_context io;
  tcp::socket socket(io);
  return 0;
}