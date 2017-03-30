#include "NetworkManager.h"
#include "Client.h"

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
		printf("Socket Creation FAILED!\n");
		return false;
	}
	return true;
}

boolean NetworkManager::bindSocket()
{
	destination.sin_port = htons(port);
	destination.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (struct sockaddr *)&destination, sizeof(destination)) < 0) {
		printf("Binding Socket FAILED!\n");
		closeSocket();
		return false;
	}
	return true;
}

boolean NetworkManager::listenOnSocket()
{
	printf("\nListening\n");
	if (listen(serverSocket, 5) < 0) {
		printf("Listening on Socket FAILED!\n");
		closeSocket();
		return false;
	}
	return true;
}

boolean NetworkManager::acceptConnection()
{

	struct sockaddr_in clientAddress;
	int clientSize = sizeof(clientAddress);
	pthread_t sniffer_thread[MAXSOCK];
	int c = 0;
	while (true) {

		int sock = accept(serverSocket, (struct sockaddr *)&clientAddress, (int *)&clientSize);
		if (sock < 0)
		{
			printf("Socket Connection FAILED!\n");
			closeSocket();
			return false;
		}
		
		int p = -1;
		Client client(sock);
		if (p = pthread_create(&sniffer_thread[c], NULL, connection_handler, (void*)&client) < 0)
		{
			perror("could not create thread\n");
			return 1;
		}		
		c++;
	}
	return true;
}

void *NetworkManager::connection_handler(void *sClient)
{	
	Client client = *(Client*)sClient;
	client.getSock();		
	return 0;
}