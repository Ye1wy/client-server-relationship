#include <iostream>

#include "include/client.h"

int main() {
  try {
    chain::Client client;

    client.Connect();
    client.Start();

  } catch (const std::exception& e) {
    std::cerr << "Client error: " << e.what() << std::endl;
  }

  return 0;
}