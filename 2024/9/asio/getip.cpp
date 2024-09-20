#include <boost/asio.hpp>
#include <iostream>
#include <string>

int main() {
  std::string host;
  std::cin >> host;
  boost::asio::io_service service;
  boost::asio::ip::tcp::resolver resolver(service);
  boost::asio::ip::tcp::resolver::query query(host, "80");
  boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
  boost::asio::ip::tcp::endpoint ep = *iter;
  std::cout << ep.address().to_string() << std::endl;
  return 0;
}