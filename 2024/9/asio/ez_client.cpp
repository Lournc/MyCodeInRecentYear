#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

void handle_read(boost::asio::streambuf &buffer) {
  std::istream response_stream(&buffer);
  std::string response_line;

  // 读取响应的头部信息并打印
  while (std::getline(response_stream, response_line) &&
         response_line != "\r") {
    std::cout << response_line << std::endl;
  }

  // 打印分隔符（用于显示头部和正文之间的空行）
  std::cout << "\n";

  // 输出正文内容
  if (response_stream.rdbuf()->in_avail() > 0) {
    std::string body;
    std::getline(response_stream, body);
    std::cout << "Response body: " << body << std::endl;
  }
}

void send_request(boost::asio::io_context &io_context,
                  const std::string &server, const std::string &port) {
  tcp::resolver resolver(io_context);
  auto endpoints = resolver.resolve(server, port);
  tcp::socket socket(io_context);
  boost::asio::connect(socket, endpoints);

  // 发送 HTTP GET 请求
  std::string request =
      "GET / HTTP/1.1\r\nHost: " + server + "\r\nConnection: close\r\n\r\n";
  boost::asio::write(socket, boost::asio::buffer(request));

  // 接收并解析服务器的响应
  boost::asio::streambuf response_buffer;
  boost::asio::read_until(socket, response_buffer, "\r\n\r\n");

  handle_read(response_buffer); // 处理并输出响应

  // 读取剩下的正文
  boost::asio::read(socket, response_buffer, boost::asio::transfer_all());
  handle_read(response_buffer);
}

int main() {
  try {
    boost::asio::io_context io_context;
    std::string server = "127.0.0.1"; // 服务器地址
    std::string port = "8080";        // 服务器端口
    send_request(io_context, server, port);
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
