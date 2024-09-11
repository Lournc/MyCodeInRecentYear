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

void session(tcp::socket sock) {
  try {
    char data[1024];
    boost::system::error_code error;

    // 读取客户端请求
    size_t length = sock.read_some(boost::asio::buffer(data), error);

    if (!error) {
      // 打印接收到的请求（可以用来调试）
      std::cout << "Request received:\n"
                << std::string(data, length) << std::endl;

      // 发送 HTTP 响应
      std::string response = make_response();
      boost::asio::write(sock, boost::asio::buffer(response));
    }
  } catch (std::exception &e) {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

int main() {
  try {
    boost::asio::io_context io_context;

    // 监听端口 8080
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

    std::cout << "Server is running on port 8080...\n";

    // 不断接受客户端连接
    while (true) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      // 每次连接创建一个线程处理请求
      std::thread(session, std::move(socket)).detach();
    }
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}