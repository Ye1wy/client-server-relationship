#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H

#include <sys/socket.h>

#include <algorithm>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "socket.h"

#define MAX_LENGHT 64

namespace chain {

class Client {
 public:
  Client();
  ~Client() = default;

  void Start();
  void InputThread();
  void ProcessingThread();
  void Connect();
  bool Send();

 private:
  std::string data_;
  Socket client_socket_;
  std::mutex mtx_;
  std::condition_variable cv_;

  bool status_send_data_;
  bool is_connected_done_;

  bool Valid(const std::string verifiable) const noexcept;
  bool IsDigits(const std::string &str) const;
  void HandlingData(std::string &data) noexcept;
};
}  // namespace chain

#endif