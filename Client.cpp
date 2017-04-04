#include "Client.h"

Client::Client(int sSock)
{
	socket = sSock;
}

int Client::getSocket() {
	printf("Client connected: %i \n", socket);

	return socket;
}

void Client::sendMessage(char* buffer, int size) {
	int result = send(socket, buffer, size, 0);
}