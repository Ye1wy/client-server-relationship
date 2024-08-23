#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H

#include <sys/socket.h>

#include <algorithm>
#include <iostream>
#include <string>

#define MAX_LENGHT 64

namespace chain {

class Client {
 public:
  Client();
  ~Client() = default;

  void DataCatch(std::string incomming);

 private:
  std::string data_;

  bool Valid(const std::string verifiable) const noexcept;
  bool IsDigits(const std::string &str) const;
  void HandlingData(std::string &data) noexcept;
};
}  // namespace chain

#endif