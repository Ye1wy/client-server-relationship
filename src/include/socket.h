#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SOCKET_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SOCKET_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdexcept>

#define PORT 8080

namespace chain {

using FileDescriptorType = int;
using AddressFamily = sa_family_t;
using SocketType = int;
using ProtocolType = int;
using Address = struct sockaddr_in;

enum class SocketStatus {
  kConnected = 0,
  kErrorBind = 1,
  kErrorListen = 2,
  kErrorAccept = 3,
  kErrorConnect = 4,
  kErrorSocketOpen = 5,
  kDisconnect = 6,
};

class Socket {
 public:
  Socket(FileDescriptorType fd = 0, AddressFamily address_family = AF_INET,
         SocketType = SOCK_STREAM, ProtocolType = 0);
  Socket(const Socket&) = delete;
  Socket(Socket&& other) noexcept;
  virtual ~Socket();

  Socket& operator=(const Socket&) = delete;
  Socket& operator=(Socket&&) = delete;

  void Bind();
  void Listen(int backlog = 3);
  Socket Accept();

  void Connect();

  FileDescriptorType get_file_descriptor() const noexcept;
  Address get_address_f() const noexcept;
  int get_socket_status() const noexcept;

 private:
  void Close();

  SocketType socket_type_;
  FileDescriptorType fd_;

  Address address_f_;
  socklen_t addrlen_;
  SocketStatus status_;
};

}  // namespace chain

#endif