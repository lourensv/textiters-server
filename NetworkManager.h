#pragma once
#include <iostream>
#include <pthread.h>

#ifdef _WIN32
#pragma comment(lib , "ws2_32.lib")
#include <winsock.h>
#endif

#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
	boolean createSocket();
	boolean bindSocket();
	boolean listenOnSocket();
	boolean acceptConnection();

	int port;
	int serverSocket;
	struct sockaddr_in destination;
};