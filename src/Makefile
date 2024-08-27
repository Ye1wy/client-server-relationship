CXX=g++
CXXFLAGS=-Wall -Werror -Wextra -lpthread
UNAME_S = $(shell uname -s)
DISTRO = $(shell lsb_release -is)

OSFLAGS =

ifeq ($(UNAME_S),Linux)
    ifeq ($(DISTRO),Ubuntu)
        OSFLAGS+=-lsubunit -lm
        CXXFLAGS+=$(OSFLAGS)
        @echo "Detected Ubuntu"
    endif
endif

CLIENT_SRC=$(PWD)/build/client_main.o $(PWD)/build/client.o $(PWD)/build/socket.o
SERVER_SRC=$(PWD)/build/server_main.o $(PWD)/build/server.o $(PWD)/build/socket.o

all: build

build: socket.o client.o server.o aplications.exe

rebuild: clean build

socket.o:
	@mkdir build
	@$(CXX) -c $(CXXFLAGS) $(PWD)/socket/base/socket.cc -o build/socket.o

client.o:
	@echo "Compiling client..."
	@$(CXX) -c $(CXXFLAGS) $(PWD)/client/client_main.cc -o build/client_main.o
	@$(CXX) -c $(CXXFLAGS) $(PWD)/client/base/client.cc -o build/client.o
	@echo "Client compilation completed."
	
server.o:
	@echo "Compile server..."
	@$(CXX) -c $(CXXFLAGS) $(PWD)/server/server_main.cc -o build/server_main.o
	@$(CXX) -c $(CXXFLAGS) $(PWD)/server/base/server.cc -o build/server.o
	@echo "Server compilation completed."
	
aplications.exe:
	@echo "Wait a little more..."
	@$(CXX) $(CXXFLAGS) $(SERVER_SRC) -o server_exe
	@$(CXX) $(CXXFLAGS) $(CLIENT_SRC) -o client_exe
	@rm -rf build
	@echo "All done."

debug: clean
	@$(CXX) $(CXXFLAGS) $(CLIENT_SRC) -g -o client_exe
	@$(CXX) $(CXXFLAGS) $(SERVER_SRC) -g -o server_exe
	
clean:
	@rm -f client_exe server_exe
	@rm -rf build
	@echo "Clean completed."