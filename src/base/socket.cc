#include "include/socket.h"

chain::Socket::Socket(FileDescriptorType fd, AddressFamily address_family,
                      SocketType socket_type, ProtocolType protocol)
    : socket_type_(socket_type),
      fd_(socket(address_family, socket_type, protocol)),
      status_(chain::SocketStatus::kConnected) {
  if (fd_ < 0) {
    status_ = chain::SocketStatus::kErrorSocketOpen;
    throw std::runtime_error("Socket failed");
  }

  if (inet_pton(address_family, "127.0.0.1", &address_f_.sin_addr) == 0) {
    status_ = chain::SocketStatus::kErrorSocketOpen;
    throw std::runtime_error("Invalide address");
  }

  address_f_.sin_family = address_family;
  address_f_.sin_port = htons(PORT);  // PORT равен 8080
  addrlen_ = sizeof(address_f_);
}

chain::Socket::Socket(Socket &&other) noexcept
    : socket_type_(other.socket_type_),
      fd_(other.fd_),
      address_f_(other.address_f_),
      addrlen_(other.addrlen_) {
  other.fd_ = -1;
}

chain::Socket::~Socket() { Close(); }

void chain::Socket::Bind() {
  if (bind(fd_, reinterpret_cast<sockaddr *>(&address_f_), sizeof(address_f_)) <
      0) {
    status_ = chain::SocketStatus::kErrorBind;
    throw std::runtime_error("Bind failed");
  }
}

void chain::Socket::Listen(int backlog) {
  if (listen(fd_, backlog) < 0) {
    status_ = chain::SocketStatus::kErrorListen;
    throw std::runtime_error("Listen failed");
  }
}

chain::Socket chain::Socket::Accept() {
  FileDescriptorType new_socket;
  new_socket =
      accept(fd_, reinterpret_cast<sockaddr *>(&address_f_), &addrlen_);

  if (new_socket < 0) {
    status_ = chain::SocketStatus::kErrorAccept;
    throw std::runtime_error("Accept failed");
  }

  return Socket(new_socket, address_f_.sin_family, socket_type_, 0);
}

void chain::Socket::Connect() {
  if (connect(fd_, reinterpret_cast<sockaddr *>(&address_f_), addrlen_) < 0) {
    status_ = chain::SocketStatus::kErrorConnect;
    throw std::runtime_error("Connection failed");
  }
}

void chain::Socket::Close() {
  if (fd_ >= 0) {
    close(fd_);
    fd_ = -1;
  }
}

chain::FileDescriptorType chain::Socket::get_file_descriptor() const noexcept {
  return fd_;
}

chain::Address chain::Socket::get_address_f() const noexcept {
  return address_f_;
}

int chain::Socket::get_socket_status() const noexcept {
  return static_cast<int>(status_);
}