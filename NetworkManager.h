#pragma once
#include <iostream>
#include <pthread.h>

#ifdef _WIN32
#pragma comment(lib , "ws2_32.lib")
#include <winsock.h>
#endif

#ifndef _WIN32
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#define MAXSOCK 70000

class NetworkManager
{
public:
	NetworkManager(int aPort);
	int startServer();
	static void *connection_handler(void *socket_desc);

private:
	void closeSocket();
	bool createSocket();
	bool bindSocket();
	bool listenOnSocket();
	bool acceptConnection();

	int port;
	int serverSocket;
	struct sockaddr_in destination;
};