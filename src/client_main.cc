#include "include/client.h"

int main() {
  chain::Client net;

  std::string data;
  while (1) {
    std::cin >> data;

    net.DataCatch(data);
  }
}