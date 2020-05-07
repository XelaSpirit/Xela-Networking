#ifndef _XELA_CLIENT_H
#define _XELA_CLIENT_H

#include "XelaNetworking.h"
#include "XelaSocket.h"

#if XELANETWORK_DEBUG_CLIENT
#include <iostream>
#endif

extern "C" {
	struct XelaClient {
		//Whether or not this client is currently open
		bool isOpen = true;
		int proto = -1;

		#if defined(_WIN32)
		addrinfo hints;
		SOCKET connectSock = INVALID_SOCKET;

		static XELANETWORK_HIDDEN XelaSocket *initWindows(char *ip, char *port, addrinfo *hints, SOCKET *connectSock, bool *open, int protocol, int *success);
		static XELANETWORK_HIDDEN int connectTCPWindows(char *ip, char *port, addrinfo *addrResult, SOCKET *connectSock, bool *open);
		#elif defined(__linux__)
		int sockfd;
		sockaddr_in serverAddr;
		hostent *server;

		static XELANETWORK_HIDDEN int connectTCPLinux(int *sockfd, sockaddr_in *serverAddr, char *ip, char *port);
		static XELANETWORK_HIDDEN XelaSocket *initLinux(char *ip, char *port, int *sockfd, sockaddr_in *serverAddr, hostent **server, bool *open, int protocol, int *success);
		#endif

		//Success is set to 0 on success, and set to an error code otherwise
		static XELANETWORK_API XelaClient *genClient(int protocol, int *success);

		//Connect to a server at ip:port
		//Success set to 0 on success, set to an error code otherwise
		static XELANETWORK_API XelaSocket *connectClient(XelaClient *c, char *ip, char *port, int *success);
	};
}

#endif