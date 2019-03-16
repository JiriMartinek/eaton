all: server client

client: client.cpp

server:
	g++ -pthread server.cpp -o server
