#include "main.h""
#include "NetworkManager.h"

int main(int argc, char *argv[])
{
	NetworkManager networkManager(PORT);
	networkManager.startServer();
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