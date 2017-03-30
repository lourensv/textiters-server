#pragma once

#include <iostream>

class Client
{
public:
	Client(int sock);
	int getSock();

private:
	int sock;
};