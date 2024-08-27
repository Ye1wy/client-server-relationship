#include "../include/server.h"

chain::Server::Server()
    : data_(),
      server_listener_(),
      client_connections_(),
      server_work_status_(true) {
  server_listener_.Bind();
  server_listener_.Listen();
}

void chain::Server::Run() {
  while (true) {
    try {
      client_connections_ =
          std::move(server_listener_.Accept());  // Принимаем соединение
      HandleClient();  // Обработка клиента

    } catch (const std::exception& e) {
      std::cerr << "Server: " << e.what() << std::endl;
      server_work_status_ = false;
    }
  }
}

void chain::Server::HandleClient() {
  bool client_connected = true;

  while (client_connected) {
    char buffer[1024] = {0};
    int bytes_read = recv(client_connections_.get_file_descriptor(), buffer,
                          sizeof(buffer), 0);

    if (bytes_read > 0) {
      buffer[bytes_read] = '\0';
      data_ = buffer;
      Analyse();

    } else if (bytes_read == 0) {
      std::cout << "Server: Client disconnected" << std::endl;
      client_connected = false;

    } else if (bytes_read == -1) {
      perror("Server: Read error");
      std::cout << "Error code: " << errno << std::endl;
      client_connected = false;
    }
  }

  client_connections_.Stop();
}

void chain::Server::Analyse() {
  std::cout << "Taked data: " << data_ << std::endl;
}

int chain::Server::is_work() const noexcept { return server_work_status_; }