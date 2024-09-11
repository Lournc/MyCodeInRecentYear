#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

std::string make_response() {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html\r\n"
         "Content-Length: 13\r\n"
         "\r\n"
         "Hello, World!";
}

class session : public std::enable_shared_from_this<session> {
public:
  session(tcp::socket socket) : socket_(std::move(socket)) {}

  void start() { do_read(); }

private:
  void do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_),
        [this, self](boost::system::error_code ec, std::size_t length) {
          if (!ec) {
            std::cout << "Request received:\n"
                      << std::string(data_, length) << std::endl;
            do_write();
          }
        });
  }

  void do_write() {
    auto self(shared_from_this());
    std::string response = make_response();
    boost::asio::async_write(
        socket_, boost::asio::buffer(response),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            socket_.shutdown(tcp::socket::shutdown_both);
          }
        });
  }

  tcp::socket socket_;
  char data_[1024];
};

class server {
public:
  server(boost::asio::io_context &io_context, short port)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
  }

private:
  void do_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
          if (!ec) {
            std::make_shared<session>(std::move(socket))->start();
          }
          do_accept();
        });
  }

  tcp::acceptor acceptor_;
};

int main() {
  try {
    boost::asio::io_context io_context;

    server s(io_context, 8080);

    std::cout << "Server is running on port 8080...\n";
    io_context.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
