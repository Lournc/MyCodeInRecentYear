#include <algorithm>
#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <memory>
#include <vector>

using boost::asio::ip::tcp;
using namespace std;

class ChatSession : public std::enable_shared_from_this<ChatSession> {
public:
  ChatSession(tcp::socket socket, vector<shared_ptr<ChatSession>> &clients)
      : socket_(std::move(socket)), clients_(clients) {
    cout << "New session started." << endl;
  }

  void start() {
    clients_.emplace_back(shared_from_this());
    cout << "Client connected. Total clients: " << clients_.size() << endl;
    doRead();
  }

  void deliver(const string &msg) {
    bool writeInProgress = !writeMsgs_.empty();
    writeMsgs_.push_back(msg);
    if (!writeInProgress) {
      doWrite();
    }
  }

private:
  void doRead() {
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_, maxLength),
        [this, self](boost::system::error_code ec, size_t length) {
          if (!ec) {
            string msg(data_, length);
            cout << "Received message: " << msg << endl;
            for (auto &client : clients_) {
              if (client != self) {
                client->deliver(msg);
              }
            }
            doRead();
          } else {
            cout << "Client disconnected. Error: " << ec.message() << endl;
            auto it = std::find(clients_.begin(), clients_.end(), self);
            if (it != clients_.end()) {
              clients_.erase(it);
            }
            cout << "Total clients: " << clients_.size() << endl;
          }
        });
  }

  void doWrite() {
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(writeMsgs_.front().data(),
                            writeMsgs_.front().length()),
        [this, self](boost::system::error_code ec, size_t /*length*/) {
          if (!ec) {
            writeMsgs_.pop_front();
            if (!writeMsgs_.empty()) {
              doWrite();
            }
          } else {
            cout << "Failed to send message. Error: " << ec.message() << endl;
            auto it = std::find(clients_.begin(), clients_.end(), self);
            if (it != clients_.end()) {
              clients_.erase(it);
            }
            cout << "Total clients: " << clients_.size() << endl;
          }
        });
  }

  tcp::socket socket_;
  vector<shared_ptr<ChatSession>> &clients_;
  enum { maxLength = 1024 };
  char data_[maxLength];
  deque<string> writeMsgs_;
};

class ChatServer {
public:
  ChatServer(boost::asio::io_context &ioContext, short port)
      : acceptor_(ioContext, tcp::endpoint(tcp::v4(), port)),
        socket_(ioContext) {
    cout << "Server started on port " << port << endl;
    doAccept();
  }

private:
  void doAccept() {
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
      if (!ec) {
        std::make_shared<ChatSession>(std::move(socket_), clients_)->start();
      } else {
        cout << "Accept error: " << ec.message() << endl;
      }
      doAccept();
    });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
  vector<shared_ptr<ChatSession>> clients_;
};

int main() {
  try {
    boost::asio::io_context ioContext;

    ChatServer server(ioContext, 8888);

    ioContext.run();
  } catch (std::exception &e) {
    cerr << "Exception: " << e.what() << endl;
  }

  return 0;
}
