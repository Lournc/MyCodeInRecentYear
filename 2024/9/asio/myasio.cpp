#include <boost/asio.hpp>
#include <boost/asio/buffered_read_stream.hpp>
#include <iostream>
#include <string>

void connect_handler(const boost::system::error_code &ec) {
  if (ec)
    return;
  std::cout << "ABC";
}

int main() {
  boost::asio::io_context ctx;
  boost::asio::ip::tcp::socket socket{ctx};
  boost::asio::ip::tcp::endpoint endpoint{
      boost::asio::ip::address::from_string("127.0.0.1"), 1214};
  boost::system::error_code ec;
  socket.async_connect(endpoint, connect_handler);
  ctx.run();

  boost::asio::buffered_read_stream<std::stringstream> data;
  socket.async_read
      // duckdb::DuckDB db("data.db");
      // duckdb::Connection con{db};
      return 0;
}