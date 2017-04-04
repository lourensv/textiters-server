#pragma once

#ifdef _WIN32
#pragma comment(lib , "ws2_32.lib")
#include <winsock.h>
#endif

#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
