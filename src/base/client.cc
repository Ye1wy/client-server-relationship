#include "../include/client.h"

chain::Client::Client()
    : data_(std::string()),
      client_socket_(),
      mtx_(),
      cv_(),
      status_send_data_(false),
      is_connected_done_(false) {};

void chain::Client::Start() {
  std::thread input_thread(&Client::InputThread, this);
  std::thread processing_thread(&Client::ProcessingThread, this);

  input_thread.join();
  processing_thread.join();
}

void chain::Client::InputThread() {
  std::string tmp_data;

  while (true) {
    std::cin >> tmp_data;

    if (!Valid(tmp_data)) {
      std::cout << "You input not valide string" << std::endl;
      continue;
    }

    {
      std::lock_guard<std::mutex> lock(mtx_);
      data_ = tmp_data;
      status_send_data_ = false;
    }

    cv_.notify_one();
  }
}

void chain::Client::ProcessingThread() {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock);

    status_send_data_ = true;

    HandlingData(data_);

    client_socket_.Send(data_);
  }
}

void chain::Client::Connect() {
  if (is_connected_done_) {
    throw std::logic_error("Client is already connected!");
  }

  client_socket_.Connect();
  is_connected_done_ = true;
}

bool chain::Client::Send() {
  if (!status_send_data_) {
    throw std::runtime_error("Somthing went wrong! Thread handling ERROR");
  }

  if (!is_connected_done_) {
    throw std::logic_error("Socket Client is not connected");
  }

  client_socket_.Send(data_);

  return true;
}

void chain::Client::HandlingData(std::string &data) noexcept {
  std::sort(data.begin(), data.end());

  // for (auto it = data.begin(); it != data.end(); ++it) {
  //   std::cout << *it << std::endl;
  // }

  std::cout << "all sorted" << std::endl;
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