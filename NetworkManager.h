#pragma once
#include <iostream>
#include <pthread.h>
#include <stdio.h>

#include "sockets.h"

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
