#include "include/socket.h"

chain::Socket::Socket(FileDescriptorType fd, AddressFamily address_family,
                      SocketType socket_type, ProtocolType protocol) {
  fd_ = socket(address_family, socket_type, protocol);

  if (fd_ < 0) {
    status_ = chain::SocketStatus::kErrorSocketOpen;
    throw "Socket failed";
  }

  int status;
  status = inet_pton(address_family, "127.0.0.1", &address_f_.sin_addr);

  if (status == 0) {
    status_ = chain::SocketStatus::kErrorSocketOpen;
    throw "Invalide address";
  }

  address_f_.sin_family = address_family;
  address_f_.sin_port = htons(PORT);
  addrlen_ = sizeof(address_f_);
}

chain::Socket::Socket(Socket &&other) {
  socket_type_ = other.socket_type_;
  fd_ = other.fd_;
  address_f_ = other.address_f_;
  addrlen_ = other.addrlen_;

  other.socket_type_ = SocketType();
  other.fd_ = FileDescriptorType();
  other.address_f_ = Address();
  other.addrlen_ = socklen_t();
}

chain::Socket::~Socket() { Close(); }

void chain::Socket::Bind() {
  int status =
      bind(fd_, reinterpret_cast<sockaddr *>(&address_f_), sizeof(address_f_));

  if (status < 0) {
    status_ = chain::SocketStatus::kErrorBind;
    throw "Bind failed";
  }
}

void chain::Socket::Listen() {
  int status = listen(fd_, 3);

  if (status < 0) {
    status_ = chain::SocketStatus::kErrorListen;
    throw "Listen failed";
  }
}

chain::FileDescriptorType chain::Socket::Accept() {
  FileDescriptorType new_socket;
  new_socket =
      accept(fd_, reinterpret_cast<sockaddr *>(&address_f_), &addrlen_);

  if (new_socket < 0) {
    status_ = chain::SocketStatus::kErrorAccept;
    throw "Accept failed";
  }

  return new_socket;
}

void chain::Socket::Connect() {
  int status =
      connect(fd_, reinterpret_cast<sockaddr *>(&address_f_), addrlen_);

  if (status < 0) {
    status_ = chain::SocketStatus::kErrorConnect;
    throw "Connection failed";
  }
}

void chain::Socket::Close() { close(fd_); }

chain::FileDescriptorType chain::Socket::get_file_descriptor() const noexcept {
  return fd_;
}

chain::Address chain::Socket::get_address_f() const noexcept {
  return address_f_;
}

int chain::Socket::get_socket_status() const noexcept {
  return static_cast<int>(status_);
}