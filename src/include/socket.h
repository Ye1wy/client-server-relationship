#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SOCKET_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SOCKET_H

// #include "address.h"
#include "include.h"

namespace chain {

using FileDescriptorType = int;
using AddressFamily = sa_family_t;
using SocketType = int;
using ProtocolType = int;
using Address = struct sockaddr_in;

enum class SocketStatus : int {
  connected = 0,
  disconnected = 4,
};

class Socket {
 public:
  Socket(FileDescriptorType fd = 0, AddressFamily address_family = AF_INET,
         SocketType = SOCK_STREAM, ProtocolType = 0);
  Socket(const Socket&) = delete;
  Socket(Socket&& other) noexcept;
  ~Socket();

  Socket& operator=(const Socket&) = delete;
  Socket& operator=(Socket&&) = delete;

  void Bind();
  void Listen();
  Socket Accept();

  void Connect();

  FileDescriptorType get_file_descriptor() const noexcept;
  Address get_address_f() const noexcept;

 private:
  void Close();

  SocketType socket_type_;
  FileDescriptorType fd_;

  Address address_f_;
  socklen_t addrlen_;
};

}  // namespace chain

#endif