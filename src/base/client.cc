#include "../include/client.h"

chain::Client::Client() : data_(std::string()) {};

void chain::Client::DataCatch(std::string incomming) {
  if (Valid(incomming)) {
    std::cout << "You input not valide string" << std::endl;
    return;
  }

  HandlingData(incomming);

  data_ = incomming;
}

void chain::Client::HandlingData(std::string &data) noexcept {
  std::sort(data.begin(), data.end());

  for (auto it = data.begin(); it != data.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

bool chain::Client::IsDigits(const std::string &str) const {
  for (char ch : str) {
    if (!isdigit(ch)) {
      return false;
    }
  }

  return true;
}

bool chain::Client::Valid(const std::string verifiable) const noexcept {
  if (verifiable.length() > MAX_LENGHT) {
    return false;
  }

  if (!IsDigits(verifiable)) {
    return false;
  }

  return true;
}