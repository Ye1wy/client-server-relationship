#include "../include/client.h"

chain::Client::Client()
    : data_(std::string()),
      client_socket_(),
      mtx_(),
      cv_(),
      data_status_(false) {};

void chain::Client::Start() {
  std::thread input_thread(&Client::InputThread, this);
  std::thread processing_thread(&Client::ProcessingThread, this);

  input_thread.join();
  input_thread.join();
}

void chain::Client::InputThread() {
  std::string tmp_data;

  while (true) {
    std::cin >> tmp_data;

    if (!Valid(tmp_data)) {
      std::cout << "You input not valide string" << std::endl;
      return;
    }

    {
      std::lock_guard<std::mutex> lock(mtx_);
      data_ = tmp_data;
      data_status_ = true;
    }

    cv_.notify_one();
  }
}

void chain::Client::ProcessingThread() {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock);

    data_status_ = false;

    HandlingData(data_);
  }
}

bool chain::Client::SendData() const {
  ssize_t send_status;

  const char *c_str = data_.c_str();

  send_status =
      send(client_socket_.get_file_descriptor(), c_str, data_.length(), 0);

  if (send_status == -1) {
    std::cout << "Cannot sand data!" << std::endl;
    return false;
  }

  return true;
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