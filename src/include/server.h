#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SERVER_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SERVER_H

#include <sys/socket.h>

#include <iostream>

#include "socket.h"

namespace chain {

class Server {
 public:
  Server();
  ~Server() = default;

  void Run();

  int is_work() const noexcept;

 private:
  void HandleClient();
  void Analyse();

  std::string data_;
  Socket server_listener_;
  Socket client_connections_;
  bool server_work_status_;
};
}  // namespace chain

#endif