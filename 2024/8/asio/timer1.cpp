#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

int main() {
  io_context io;
  steady_timer t(io, chrono::seconds(5));
  t.wait();
  std::cout << "Hello, world!" << std::endl;
  return 0;
}