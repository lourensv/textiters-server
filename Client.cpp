#include "Client.h"

Client::Client(int sSock)
{
	socket = sSock;
}

int Client::getSocket() 
{
	printf("Client connected: %i \n", socket);

	return socket;
}

void Client::startMessageReceiver()
{
	char buffer[256];
	char msg[] = "Message received\n";
	while (true) 
	{
		int size = recv(socket, buffer, 256, 0);
		
		printf("Message from %d, size %d: %.*s\n", socket, size, size, buffer);
		if (size < 0) 
		{
			printf("%d error - disconnected\n", socket);
			break;
		}
		if (size == 0) 
		{
			printf("%d disconnected\n", socket);
			break;
		}			
		sendMessage(msg, sizeof(msg));
	}
	printf("%d done\n", socket);
}

void Client::sendMessage(char* buffer, int size) 
{
	printf("Sending Message to %d, size %d: %.*s\n", socket, size, size, buffer);
	int result = send(socket, buffer, size, 0);
}