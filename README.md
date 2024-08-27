# CPP client-server relationship
### Client-server relationship both two applications based on Linux sockets writed on C++ programming language
# Introduction
## First Appliication (Client)
### The client connects to the server automatically. The client can reconnect to the server and send data.
### **Client** specializes in endlessly requesting data, processing it, and sending this data to the server if it is correct.
### If the server becomes unreachable, the client will notify about this and ask the user to reconnect.

### The client has 1 command available, in addition to data requests:
### `reconnect` - will reconnect to the server
## Second Application (Server)
### The server is capable of receiving data from the client and processing its sent data.
### The server is specialized in such a way that it can automatically process data coming from the client and output the correctness of this data. When the client disconnects, the server will notify about the client disconnection, but will still wait for data.

# Installation
```
cd src
make
```

# Launching
## Server
```
./server_exe
```
## Client
```
./client_exe
```
