#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H

#include <sys/socket.h>

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "../../socket/include/socket.h"

#define MAX_LENGHT 64
#define RECONNECT_INTERVAL 5

namespace chain {

class Client {
 public:
  Client();
  ~Client() = default;

  void Start();
  bool Connect();

 private:
  std::string data_;
  Socket client_socket_;
  std::mutex mtx_;
  std::condition_variable cv_;

  bool status_send_data_;
  bool is_connection_made_;

  void Send(std::string data);
  void Reconnect();
  void AttemptReconnect();
  void InputThread();
  void ProcessingThread();

  bool Valid(const std::string verifiable) const noexcept;
  bool IsDigits(const std::string &str) const;
  void PrimaryProcessing(std::string &data) noexcept;
  int SecondaryProcessing() noexcept;
};
}  // namespace chain

#endif