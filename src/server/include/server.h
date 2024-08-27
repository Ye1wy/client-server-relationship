#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SERVER_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SERVER_H

#include <sys/socket.h>

#include <iostream>

#include "../../socket/include/socket.h"

namespace chain {

class Server {
 public:
  Server();
  ~Server() = default;

  void Run();

  int is_work() const noexcept;

 private:
  void Analyse(std::string data);

  Socket server_listener_;
  bool server_work_status_;
};
}  // namespace chain

#endif