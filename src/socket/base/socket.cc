#include "../include/socket.h"

chain::Socket::Socket(FileDescriptorType fd, AddressFamily address_family,
                      SocketType socket_type, ProtocolType protocol)
    : fd_(fd),
      address_f_(address_family),
      socket_type_(socket_type),
      protocol_(protocol),
      address_(),
      addrlen_(),
      status_() {
  bzero((char *)&address_, sizeof(address_));

  if (fd <= 0) {
    SocketUp();

  } else {
    fd_ = fd;
  }

  int opt = 1;

  if (setsockopt(get_file_descriptor(), SOL_SOCKET, SO_REUSEADDR, &opt,
                 sizeof(opt)) < 0) {
    throw std::runtime_error("Setsockopt failed");
  }

  if (inet_pton(address_family, "127.0.0.1", &address_.sin_addr) == 0) {
    throw std::runtime_error("Invalide address");
  }

  address_.sin_family = address_family;
  address_.sin_port = htons(PORT);  // PORT равен 8080
  addrlen_ = sizeof(address_);
  status_ = chain::SocketStatus::kSocketUp;
}

chain::Socket::Socket(Socket &&other) noexcept
    : fd_(other.fd_),
      address_f_(other.address_f_),
      socket_type_(other.socket_type_),
      protocol_(other.protocol_),
      address_(other.address_),
      addrlen_(other.addrlen_),
      status_(other.status_) {
  other.fd_ = -1;
}

chain::Socket::~Socket() { Stop(); }

chain::Socket &chain::Socket::operator=(Socket &&other) noexcept {
  if (this != &other) {
    Stop();
    fd_ = other.fd_;
    protocol_ = other.protocol_;
    socket_type_ = other.socket_type_;
    address_f_ = other.address_f_;

    address_ = other.address_;
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
  FileDescriptorType new_socket;
  new_socket = accept(get_file_descriptor(),
                      reinterpret_cast<sockaddr *>(&address_), &addrlen_);

  if (new_socket < 0) {
    throw std::runtime_error("Accept failed");
  }

  return Socket(new_socket, get_address_f(), get_socket_type(), 0);
}

bool chain::Socket::Connect() {
  if (connect(fd_, reinterpret_cast<sockaddr *>(&address_), addrlen_) < 0) {
    std::cout << "Connection failed! Try reconnecting to the server or try "
                 "again later"
              << std::endl;
    perror("Error:");
    std::cout << "Error code: " << errno << std::endl << std::endl;
    return false;
  }

  return true;
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

void chain::Socket::SocketUp() {
  fd_ = socket(get_address_f(), get_socket_type(), get_protocol_type());

  if (fd_ < 0) {
    throw std::runtime_error("Socket failed");
  }

  status_ = chain::SocketStatus::kSocketUp;
}

void chain::Socket::Stop() {
  if (status_ == chain::SocketStatus::kSocketUp) {
    close(fd_);
    fd_ = -1;

  } else {
    throw std::runtime_error("Somthing went wrong in stoping socket...");
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

chain::ProtocolType chain::Socket::get_protocol_type() const noexcept {
  return protocol_;
}

chain::Address chain::Socket::get_address() const noexcept { return address_; }

int chain::Socket::get_socket_status() const noexcept {
  return static_cast<int>(status_);
}