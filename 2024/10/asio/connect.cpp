#include <boost/asio.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

int main() {
  try {
    boost::asio::io_context ctx;
    boost::asio::ip::tcp::resolver resolver(ctx);
    auto ep = resolver.resolve("cs144.keithw.org", "http");
    boost::asio::ip::tcp::socket socket(ctx);
    boost::asio::connect(socket, ep);
    std::cout << "Connect Success!\n";
    // 发送数据
    const std::string request =
        "GET / HTTP/1.1\r\nHost: cs144.keithw.org\r\nConnection: close\r\n\r\n";
    boost::asio::write(socket, boost::asio::buffer(request));

    // 接收返回数据
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    // 检查响应状态
    std::istream response_stream(&response);
    std::string http_version;
    unsigned int status_code;
    response_stream >> http_version >> status_code;

    if (http_version.substr(0, 5) != "HTTP/") {
      std::cout << "Invalid response\n";
      return 1;
    }
    if (status_code != 200) {
      std::cout << "Response returned with status code " << status_code << "\n";
      return 1;
    }

    // 读取响应内容
    boost::asio::read_until(socket, response, "\r\n\r\n");

    // 显示返回内容
    std::string header;
    while (std::getline(response_stream, header) && header != "\r")
      std::cout << header << "\n";
    std::cout << "\n";

    // 读取剩余的响应体
    std::ostringstream response_body;
    response_body << &response;
    std::cout << response_body.str();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return 0;
}