#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H

#include "include.h"
#include "socket.h"

namespace chain {

class Client {
 public:
  Client();
  ~Client() = default;

  void Start();
  void InputThread();
  void ProcessingThread();
  bool SendData() const;

 private:
  std::string data_;
  std::mutex mtx_;
  std::condition_variable cv_;

  bool data_status_;
  Socket client_socket_;

  bool Valid(const std::string verifiable) const noexcept;
  bool IsDigits(const std::string &str) const;
  void HandlingData(std::string &data) noexcept;
};
}  // namespace chain

#endif