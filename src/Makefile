GPP=g++
CFLAGS=-Wall -Werror -Wextra
ADITHONAL_FLAGS=-lpthread
CLIENT_SRC=$(PWD)/client/client_main.cc $(PWD)/client/base/client.cc $(PWD)/socket/base/socket.cc
SERVER_SRC=$(PWD)/server/server_main.cc $(PWD)/server/base/server.cc $(PWD)/socket/base/socket.cc

all: rebuild

clie:
	$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(CLIENT_SRC) -o client_exe
	
serv:
	$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(SERVER_SRC) -o server_exe
	
debug: clean
	@$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(CLIENT_SRC) -g -o client_exe
	@$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(SERVER_SRC) -g -o server_exe
		
clean:
	rm -f client_exe server_exe
	
rebuild: clean clie serv