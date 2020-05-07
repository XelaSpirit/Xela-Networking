#ifndef _XELA_SERVER_H
#define _XELA_SERVER_H

#include "XelaNetworking.h"
#include "XelaSocket.h"

extern "C" {
	struct XelaServer {
		//Whether or not this server is currently open
		bool isOpen = true, listening = false;
		int proto = -1;

		#if defined(_WIN32)
		addrinfo hints;
		SOCKET listenSock = INVALID_SOCKET;

		static XELANETWORK_HIDDEN XelaSocket *acceptTCPWindows(SOCKET sock, bool *open, int protocol, bool listening, int *success);
		static XELANETWORK_HIDDEN XelaSocket *listenUDPWindows(SOCKET sock, bool *open, int protocol, int *success);

		#elif defined(__linux__)
		int sockfd, portno;

		sockaddr_in server;

		static XELANETWORK_HIDDEN XelaSocket *acceptTCPLinux(int sockfd, bool *open, int protocol, bool listening, int *success);
		static XELANETWORK_HIDDEN XelaSocket *listenUDPLinux(int sockfd, bool *open, int protocol, int *success);
		#endif
		static XELANETWORK_HIDDEN int init_platform(XelaServer *s, char *port, int protocol);

		//Create a new server at the specified port
		//If success is set to 0, the operation was successful, otherwise there was an error
		static XELANETWORK_API XelaServer *genServer(char *port, int protocol, int *success);

		//If using TCP, will accept the next client that attempts to connect and create a new XelaSocket for that connection
		//If using UDP, will create a new XelaSocket for this server to accept data from any client that sends data to the server
		//success set to 0 on success, set to an error code otherwise
		static XELANETWORK_API XelaSocket *listenServer(XelaServer *s, int *success);
	};
}

#endif