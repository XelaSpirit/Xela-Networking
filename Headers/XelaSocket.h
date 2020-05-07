#ifndef _XELA_SOCKET_H
#define _XELA_SOCKET_H

#include "XelaNetworking.h"

#if XELANETWORK_DEBUG_SOCKET
#include <iostream>
#endif

extern "C" {
	struct XelaSocket {
		//Whether or not this socket is currently open
		bool isOpen = true;
		int proto = -1;
		//If this socket is using TCP or came from a XelaClient, this is the ip of the socket this is connection to
		char *port = nullptr;
		//If this socket is using TCP or came from a XelaClient, this is the port of the socket this is connection to
		char *ip = nullptr;

		#if defined(_WIN32)
		SOCKET connection = INVALID_SOCKET;
		#elif defined(__linux__)
		int sockfd;
		#endif

		static XELANETWORK_HIDDEN void close_platform(XelaSocket *s);

		static XELANETWORK_HIDDEN void write_platformTCP(XelaSocket *s, char *msg, int msgLen);
		static XELANETWORK_HIDDEN void write_platformUDP(XelaSocket *s, char *msg, int msgLen, char *ip, char *port);

		static XELANETWORK_HIDDEN void get_platformTCP(XelaSocket *s, char **buf, int bufLen, int *resLen, char **ip, char **port);
		static XELANETWORK_HIDDEN void get_platformUDP(XelaSocket *s, char **buf, int bufLen, int *resLen, char **ip, char **port);

		#if defined(_WIN32)
		static XELANETWORK_HIDDEN XelaSocket *genSocket(SOCKET c, int protocol, char *connectIp, unsigned short connectPort);
		#elif defined(__linux__)
		static XELANETWORK_HIDDEN XelaSocket *genSocket(int fd, int protocol, char *connectIp, char *connectPort);
		#endif

		//Close this socket
		static XELANETWORK_API void closeSocket(XelaSocket *s);
		//Sends a message to the server or client this socket is connected to
		//If toIp/toPort are set, will send to that ip. Otherwise, the ip/port used when creating the socket will be used
		//toIp/toPort are only relevant when using UDP protocol
		//For servers, toIp and toPort must be set here. For clients, toIp and toPort will be the server's port that the client connected to by default
		static XELANETWORK_API void write(XelaSocket *s, char *msg, int msgLen, char *toIp = nullptr, char *toPort = nullptr);

		//Returns the next message recieved by this socket as a string
		//If ip/port are not nullptr, they will be set to the ip/port of the sender of the message recieved
		//fromIp/fromPort are only relevant when using UDP protocol
		//buf should point to a char pointer, already initialized to be bufLen characters long
		//fromIp should be IPV4_STRLEN characters long (long enough to hold 255.255.255.255)
		//fromPort should be PORT_STRLEN characters long (long enough to hold the largest possible port; 65535)
		static XELANETWORK_API void get(XelaSocket *s, char **buf, int bufLen, int *resLen, char **fromIp = nullptr, char **fromPort = nullptr);

		//Block until there's data to read
		static XELANETWORK_API void waitForData(XelaSocket *s);
		//Returns whether or not this socket has data to read
		//This function will wait for at most timeoutSec seconds + timeoutMicroSec microseconds for data to arrive
		static XELANETWORK_API bool hasGet(XelaSocket *s, long timeoutSec = 0, long timeoutMicroSec = 0);
	};
}

#endif