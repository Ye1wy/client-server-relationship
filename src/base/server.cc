#include "../include/server.h"

chain::Server::Server() : data_(), server_socket_() {
  server_socket_.Bind();
  server_socket_.Listen();
  new_socket_after_accept = server_socket_.Accept();
}

void chain::Server::ReadData() {
  char buffer[1024] = {0};
  read(new_socket_after_accept, buffer, 1024 - 1);
  data_ = buffer;
}

void chain::Server::Analyse() {
  std::cout << "Taked data: " << data_ << std::endl;
}