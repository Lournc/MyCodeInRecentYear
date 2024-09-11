#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;
using namespace std;

class ChatClient {
public:
  ChatClient(boost::asio::io_context &ioContext, const string &host,
             const string &port)
      : ioContext_(ioContext), socket_(ioContext) {
    tcp::resolver resolver(ioContext);
    auto endpoints = resolver.resolve(host, port);
    connect(endpoints);
  }

  void write(const string &msg) {
    boost::asio::post(ioContext_, [this, msg]() {
      bool writeInProgress = !writeMsgs_.empty();
      writeMsgs_.push_back(msg);
      if (!writeInProgress) {
        doWrite();
      }
    });
  }

private:
  void connect(const tcp::resolver::results_type &endpoints) {
    boost::asio::async_connect(
        socket_, endpoints,
        [this](boost::system::error_code ec, tcp::endpoint) {
          if (!ec) {
            cout << "Connected to the server." << endl;
            doRead();
          } else {
            cout << "Failed to connect to the server. Error: " << ec.message()
                 << endl;
          }
        });
  }

  void doRead() {
    boost::asio::async_read(
        socket_, boost::asio::buffer(readMsg_, maxLength),
        [this](boost::system::error_code ec, size_t length) {
          if (!ec) {
            cout << "Received: " << string(readMsg_, length) << endl;
            doRead();
          } else {
            cout << "Connection closed by server. Error: " << ec.message()
                 << endl;
          }
        });
  }

  void doWrite() {
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(writeMsgs_.front().data(),
                            writeMsgs_.front().length()),
        [this](boost::system::error_code ec, size_t /*length*/) {
          if (!ec) {
            writeMsgs_.pop_front();
            if (!writeMsgs_.empty()) {
              doWrite();
            }
          } else {
            cout << "Failed to send message. Error: " << ec.message() << endl;
          }
        });
  }

  boost::asio::io_context &ioContext_;
  tcp::socket socket_;
  enum { maxLength = 1024 };
  char readMsg_[maxLength];
  deque<string> writeMsgs_;
};

int main() {
  try {
    boost::asio::io_context ioContext;

    ChatClient client(ioContext, "127.0.0.1", "8888");

    thread t([&ioContext]() { ioContext.run(); });

    string line;
    while (getline(cin, line)) {
      client.write(line);
    }

    t.join();
  } catch (std::exception &e) {
    cerr << "Exception: " << e.what() << endl;
  }

  return 0;
}
