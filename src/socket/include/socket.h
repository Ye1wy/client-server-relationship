#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SOCKET_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SOCKET_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>
#define PORT 8080

namespace chain {

using FileDescriptorType = int;
using AddressFamily = sa_family_t;
using SocketType = int;
using ProtocolType = int;
using Address = struct sockaddr_in;

enum class SocketStatus {
  kSocketUp = 0,
  kStop = 1,
};

class Socket {
 public:
  Socket(FileDescriptorType fd = 0, AddressFamily address_family = AF_INET,
         SocketType = SOCK_STREAM, ProtocolType = 0);
  Socket(const Socket&) = delete;
  Socket(Socket&& other) noexcept;
  ~Socket();

  Socket& operator=(const Socket&) = delete;
  Socket& operator=(Socket&&) noexcept;

  void Bind();
  void Listen(int backlog = 5);
  Socket Accept();

  bool Connect();
  std::string Send(std::string data);

  void SocketUp();
  void Stop();

  FileDescriptorType get_file_descriptor() const noexcept;
  AddressFamily get_address_f() const noexcept;
  SocketType get_socket_type() const noexcept;
  ProtocolType get_protocol_type() const noexcept;
  Address get_address() const noexcept;
  int get_socket_status() const noexcept;

 private:
  FileDescriptorType fd_;
  AddressFamily address_f_;
  SocketType socket_type_;
  ProtocolType protocol_;

  Address address_;
  socklen_t addrlen_;
  SocketStatus status_;
};

}  // namespace chain

#endif