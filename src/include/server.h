#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SERVER_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SERVER_H

#include "include.h"
#include "socket.h"

namespace chain {

class Server {
 public:
  Server();
  ~Server() = default;

  void ReadData();
  void Analyse();

 private:
  std::string data_;
  Socket server_socket_;
  FileDescriptorType new_socket_after_accept;
};
}  // namespace chain

#endif