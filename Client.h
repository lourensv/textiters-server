#pragma once

#include <iostream>
#include <stdio.h>

#include "sockets.h"

class Client
{
public:
	Client(int sock);
	int getSocket();
	void sendMessage(char* buffer, int size);

private:
	int socket;
};
