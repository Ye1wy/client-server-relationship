#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_CLIENT_H

#include "include.h"

namespace chain {

class Client {
 public:
  Client();
  ~Client() = default;

  void DataCatch(std::string incomming);
  bool Disconnect();
  bool SendData() const;

 private:
  std::string data_;

  bool Valid(const std::string verifiable) const noexcept;
  bool IsDigits(const std::string &str) const;
  void HandlingData(std::string &data) noexcept;
};
}  // namespace chain

#endif