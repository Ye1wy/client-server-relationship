GPP=g++
CFLAGS=-Wall -Werror -Wextra
ADITHONAL_FLAGS=-lpthread
CLIENT_SRC=client_main.cc base/client.cc base/socket.cc
SERVER_SRC=server_main.cc base/server.cc base/socket.cc

all: rebuild

client:
	$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(CLIENT_SRC) -o client
	
server:
	$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(SERVER_SRC) -o server
	
debug: clean
	$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(CLIENT_SRC) -g -o client
	$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(SERVER_SRC) -g -o server
		
clean:
	rm -f client server
	
rebuild: clean client server