#include <iostream>

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

#define PORT 9999

void closeSocket(int socket);

int main(int argc, char *argv[])
{
	#ifdef _WIN32
		WSADATA wsaData;
		WSAStartup(0x0202, &wsaData);
	#endif

	int thisSocket;
	struct sockaddr_in destination;

	destination.sin_family = AF_INET;
	thisSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (thisSocket < 0)
	{
		printf("\nSocket Creation FAILED!");
		return 0;
	}

	destination.sin_port = htons(PORT);
	destination.sin_addr.s_addr = INADDR_ANY;
	if (bind(thisSocket, (struct sockaddr *)&destination, sizeof(destination))<0) {
		printf("\nBinding Socket FAILED!\n");
		if (thisSocket) {
			closeSocket(thisSocket);
		}

		return 0;
	}

	printf("\nListening");
	if (listen(thisSocket, 5)<0) {
		printf("\nListening on Socket FAILED!\n");
		if (thisSocket) {
			closeSocket(thisSocket);
		}
		return 0;
	}

	struct sockaddr_in clientAddress;
	int clientSize = sizeof(clientAddress);
	thisSocket = accept(thisSocket, (struct sockaddr *)&clientAddress, (int *)&clientSize);
	if (thisSocket<0)
	{
		printf("\nSocket Connection FAILED!\n");
		if (thisSocket) {
			closeSocket(thisSocket);
		}
		return 0;
	}
	printf("\nConnection Established!");

	return 0;
}

void closeSocket(int socket) {
	#ifdef _WIN32
		WSACleanup();
	#endif

	#ifdef __linux__
		close(socket);
	#endif
}