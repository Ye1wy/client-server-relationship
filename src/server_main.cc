#include <iostream>

#include "include/server.h"

int main() {
  try {
    chain::Server server;
    server.Run();

  } catch (const std::exception& e) {
    std::cerr << "Server error: " << e.what() << std::endl;
  }

  return 0;
}