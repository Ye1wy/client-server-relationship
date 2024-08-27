GPP=g++
CFLAGS=-Wall -Werror -Wextra
ADITHONAL_FLAGS=-lpthread
CLIENT_SRC=$(PWD)/client/client_main.cc $(PWD)/client/base/client.cc $(PWD)/socket/base/socket.cc
SERVER_SRC=$(PWD)/server/server_main.cc $(PWD)/server/base/server.cc $(PWD)/socket/base/socket.cc

all: clean client_comp server_comp

client_comp:
	@$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(CLIENT_SRC) -o client_exe

server_comp:
	@$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(SERVER_SRC) -o server_exe

debug: clean
	@$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(CLIENT_SRC) -g -o client_exe
	@$(GPP) $(CFLAGS) $(ADITHONAL_FLAGS) $(SERVER_SRC) -g -o server_exe
	
clean:
	@rm -f client_exe server_exe