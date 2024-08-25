#include "../include/server.h"

chain::Server::Server() : data_(), server_socket_(), server_work_status_(true) {
  server_socket_.Bind();
  server_socket_.Listen();
}

void chain::Server::Run() {
  while (server_work_status_) {
    try {
      Socket client_socket = server_socket_.Accept();  // Принимаем соединение
      HandleClient(std::move(client_socket));  // Обрабатываем клиента

    } catch (const std::exception& e) {
      std::cerr << "Server error: " << e.what() << std::endl;
      server_work_status_ = false;
    }
  }
}

void chain::Server::HandleClient(Socket&& client_socket) {
  char buffer[1024] = {0};
  int bytes_read = read(client_socket.get_file_descriptor(), buffer, 1024 - 1);

  if (bytes_read > 0) {
    data_ = buffer;
    Analyse();

  } else if (bytes_read == 0) {
    std::cout << "Client disconnected" << std::endl;

  } else {
    std::cerr << "Read error" << std::endl;
  }
}

void chain::Server::Analyse() {
  std::cout << "Taked data: " << data_ << std::endl;
}

int chain::Server::is_work() const noexcept { return server_work_status_; }