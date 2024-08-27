#include "../include/socket.h"

chain::Socket::Socket(FileDescriptorType fd, AddressFamily address_family,
                      SocketType socket_type, ProtocolType protocol)
    : socket_type_(socket_type), address_f_(address_family), status_() {
  bzero((char *)&address_, sizeof(address_));

  fd_ = socket(address_family, socket_type, protocol);

  if (fd_ < 0) {
    throw std::runtime_error("Socket failed");
  }

  int opt = 1;

  if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    throw std::runtime_error("Setsockopt failed");
  }

  if (inet_pton(address_family, "127.0.0.1", &address_.sin_addr) == 0) {
    throw std::runtime_error("Invalide address");
  }

  address_.sin_family = address_family;
  address_.sin_port = htons(PORT);  // PORT равен 8080
  addrlen_ = sizeof(address_f_);
  status_ = chain::SocketStatus::kSocketUp;
}

chain::Socket::Socket(Socket &&other) noexcept
    : socket_type_(other.socket_type_),
      fd_(other.fd_),
      address_(other.address_),
      address_f_(other.address_f_),
      addrlen_(other.addrlen_) {
  other.fd_ = -1;
}

chain::Socket::~Socket() { Stop(); }

chain::Socket &chain::Socket::operator=(Socket &&other) noexcept {
  if (this != &other) {
    Stop();
    fd_ = other.fd_;
    socket_type_ = other.socket_type_;
    address_f_ = other.address_f_;
    addrlen_ = other.addrlen_;
  }

  return *this;
}

void chain::Socket::Bind() {
  if (bind(fd_, reinterpret_cast<sockaddr *>(&address_), sizeof(address_)) <
      0) {
    throw std::runtime_error("Bind failed");
  }
}

void chain::Socket::Listen(int backlog) {
  if (listen(fd_, backlog) < 0) {
    throw std::runtime_error("Listen failed");
  }
}

chain::Socket chain::Socket::Accept() {
  Address new_address;
  socklen_t new_address_length = sizeof(new_address);

  FileDescriptorType new_socket;
  new_socket =
      accept(get_file_descriptor(), reinterpret_cast<sockaddr *>(&new_address),
             &new_address_length);

  if (new_socket < 0) {
    throw std::runtime_error("Accept failed");
  }

  return Socket(new_socket, get_address_f(), get_socket_type(), 0);
}

void chain::Socket::Connect() {
  if (connect(fd_, reinterpret_cast<sockaddr *>(&address_), addrlen_) < 0) {
    std::cout << "Connection failed" << std::endl;
  }
}

std::string chain::Socket::Send(std::string data) {
  if (status_ == chain::SocketStatus::kStop) {
    throw std::runtime_error("Socket is Stopd");
  }

  ssize_t bytes_send =
      send(get_file_descriptor(), data.c_str(), data.length(), 0);
  std::string send_status;

  if (bytes_send > 0) {
    send_status = "Data is transmited";

  } else {
    send_status = "Cannot sand data";
  }

  return send_status;
}

void chain::Socket::Stop() {
  if (status_ == chain::SocketStatus::kSocketUp) {
    close(fd_);
    fd_ = -1;
  }

  status_ = chain::SocketStatus::kStop;
}

chain::FileDescriptorType chain::Socket::get_file_descriptor() const noexcept {
  return fd_;
}

chain::AddressFamily chain::Socket::get_address_f() const noexcept {
  return address_f_;
}

chain::SocketType chain::Socket::get_socket_type() const noexcept {
  return socket_type_;
}

chain::Address chain::Socket::get_address() const noexcept { return address_; }

int chain::Socket::get_socket_status() const noexcept {
  return static_cast<int>(status_);
}