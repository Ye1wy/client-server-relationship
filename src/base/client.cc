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
      std::cout << "Client: You input not valide string" << std::endl;
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

    Send();
  }
}

void chain::Client::Connect() {
  if (is_connected_done_) {
    std::cout << "Client: you already connected!" << std::endl;

  } else {
    client_socket_.Connect();
    is_connected_done_ = true;
  }
}

void chain::Client::Send() {
  if (!status_send_data_) {
    throw std::runtime_error("Somthing went wrong! Thread handling ERROR");
  }

  if (!is_connected_done_) {
    throw std::runtime_error("You dont connected!");
  }

  std::string send_status = client_socket_.Send(data_);
  std::cout << "Client: " << send_status << std::endl;
}

void chain::Client::HandlingData(std::string &data) noexcept {
  std::sort(data.begin(), data.end());

  // for (auto it = data.begin(); it != data.end(); ++it) {
  //   std::cout << *it << std::endl;
  // }

  std::cout << "Client: Data sorted" << std::endl;
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

void chain::Client::Reconnect() {
  while (!is_connected_done_) {
    try {
      std::cout << "Client: Attemting to reconnect..." << std::endl;
      client_socket_.Connect();
      is_connected_done_ = true;
      std::cout << "Client: Reconnected successfully" << std::endl;

    } catch (const std::exception &e) {
      std::cerr << "Client: Reconnect failed: " << e.what() << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(RECONNECT_INTERVAL));
    }
  }
}

void chain::Client::AttemptReconnect() {
  if (is_connected_done_) {
    is_connected_done_ = false;
    client_socket_.Stop();
    Reconnect();
  }
}