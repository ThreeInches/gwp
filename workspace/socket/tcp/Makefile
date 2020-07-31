all:dict_client dict_server
dict_client:tcp_socket.hpp tcp_client.hpp dict_client.cpp
	g++ -std=c++11 $^ -o $@
dict_server:tcp_socket.hpp tcp_server.hpp dict_server.cpp
	g++ -std=c++11 $^ -o $@
