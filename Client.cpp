#include "Client.h"

Client::Client(int sSock)
{
	sock = sSock;
}

int Client::getSock() {
	printf("Client connected: %i \n", sock);
	return sock;
}