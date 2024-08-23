#ifndef CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SOCKET_H
#define CPP_CLIENT_SERVER_RELATIONSHIP_INCLUDE_SOCKET_H

namespace chain {
class Socket {
 public:
  Socket(/* args */);
  ~Socket();

 private:
};

enum class SocketStatus : int {
  connected = 0,
  disconnected = 4,
};

}  // namespace chain

#endif