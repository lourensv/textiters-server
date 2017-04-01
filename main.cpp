#include "main.h"
#include "NetworkManager.h"

int main(int argc, char *argv[])
{
	NetworkManager networkManager(PORT);
	networkManager.startServer();
	return 0;
}










