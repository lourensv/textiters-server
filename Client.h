#pragma once

#include <iostream>
#include <stdio.h>

class Client
{
public:
	Client(int sock);
	int getSock();

private:
	int sock;
};
