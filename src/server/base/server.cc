#include "../include/server.h"

chain::Server::Server() : server_listener_(), server_work_status_(true) {
  server_listener_.Bind();
  server_listener_.Listen();
}

void chain::Server::Run() {
  while (true) {
    try {
      Socket client_connections_(
          server_listener_.Accept());  // accepting connection

      // Handle client data
      bool client_connected = true;

      while (client_connected) {
        char buffer[1024] = {0};
        int bytes_read = recv(client_connections_.get_file_descriptor(), buffer,
                              sizeof(buffer), 0);

        if (bytes_read > 0) {
          buffer[bytes_read] = '\0';
          Analyse(buffer);
          client_connections_.Send("Catch");

        } else if (bytes_read == 0) {
          std::cout << "Server: Client disconnected" << std::endl;
          client_connected = false;

        } else if (bytes_read == -1) {
          perror("Server: Read error");
          std::cout << "Error code: " << errno << std::endl;
          client_connected = false;
        }
      }

    } catch (const std::exception& e) {
      std::cerr << "Server: " << e.what() << std::endl;
      server_work_status_ = false;
    }
  }
}

void chain::Server::Analyse(std::string data) {
  int value = std::stoi(data);

  if ((data.length() >= 2) and ((value % 32) == 0)) {
    std::cout << "Server: Data is taked" << std::endl;

  } else {
    std::cout << "Server: Error: Inappropriate data" << std::endl;
  }
}

int chain::Server::is_work() const noexcept { return server_work_status_; }