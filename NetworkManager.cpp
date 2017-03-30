#include "NetworkManager.h"

NetworkManager::NetworkManager(int aPort)
{
	port = aPort;
}

int NetworkManager::startServer()
{
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);
#endif

	if (!createSocket()) return false;
	if (!bindSocket()) return false;
	if (!listenOnSocket()) return false;
	if (!acceptConnection()) return false;

	return true;
}

void NetworkManager::closeSocket()
{
	if (serverSocket) {
#ifdef _WIN32
		WSACleanup();
#endif

#ifdef __linux__
		close(serverSocket);
#endif
	}
}

boolean NetworkManager::createSocket()
{
	destination.sin_family = AF_INET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket < 0)
	{
		printf("\nSocket Creation FAILED!");
		return false;
	}
	return true;
}

boolean NetworkManager::bindSocket()
{
	destination.sin_port = htons(port);
	destination.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (struct sockaddr *)&destination, sizeof(destination)) < 0) {
		printf("\nBinding Socket FAILED!\n");
		closeSocket();
		return false;
	}
	return true;
}

boolean NetworkManager::listenOnSocket()
{
	printf("\nListening");
	if (listen(serverSocket, 5) < 0) {
		printf("\nListening on Socket FAILED!\n");
		closeSocket();
		return false;
	}
	return true;
}

boolean NetworkManager::acceptConnection()
{

	struct sockaddr_in clientAddress;
	int clientSize = sizeof(clientAddress);
	serverSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (int *)&clientSize);
	if (serverSocket < 0)
	{
		printf("\nSocket Connection FAILED!\n");
		closeSocket();
		return false;
	}
	printf("\nConnection Established!");
	return true;
}
