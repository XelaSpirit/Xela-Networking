#include "XelaServer.h"

#if defined(_WIN32)
void xelaSetupServerHints(addrinfo *hints, int protocol) {
	ZeroMemory(hints, sizeof(hints));
	hints->ai_family = AF_INET;			//IPv4
	hints->ai_flags = AI_PASSIVE;

	switch (protocol) {
		case XELANETWORK_PROTO_TCP:
			hints->ai_socktype = SOCK_STREAM;	//Stream socket
			hints->ai_protocol = IPPROTO_TCP;	//TCP
			break;
		case XELANETWORK_PROTO_UDP:
			hints->ai_socktype = SOCK_DGRAM;	//Datagram socket
			hints->ai_protocol = IPPROTO_UDP;	//UDP
			break;
	}
}
int XelaServer::init_platform(XelaServer *s, char *port, int protocol) {
	addrinfo *addrResult = NULL;

	xelaSetupServerHints(&s->hints, protocol);

	#if XELANETWORK_DEBUG_SERVER
	std::cout << "[XelaServer] Creating new Xela Server" << std::endl;
	std::cout << "[XelaServer] ===| AI Family: IPv4" << std::endl;
	std::cout << "[XelaServer] ===| Protocol: " << (protocol == XELANETWORK_PROTO_TCP ? "TCP" : protocol == XELANETWORK_PROTO_UDP ? "UDP" : "Other") << std::endl;
	#endif

	//Get address info
	int res = getaddrinfo(NULL, port, &s->hints, &addrResult);
	if (res != 0) {
		#if XELANETWORK_DEBUG_SERVER
		std::cout << "[XelaServer] Error on getaddrinfo: " << WSAGetLastError() << std::endl;
		#endif
		s->isOpen = false;
		return XELANETWORK_ERROR_GETADDRINFO;
	}

	//Create socket to listen with
	s->listenSock = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
	if (s->listenSock == INVALID_SOCKET) {
		#if XELANETWORK_DEBUG_SERVER
		std::cout << "[XelaServer] Error creating socket: " << WSAGetLastError() << std::endl;
		#endif
		s->isOpen = false;
		return XELANETWORK_ERROR_CREATE_SOCKET;
	}

	//Bind socket
	res = bind(s->listenSock, addrResult->ai_addr, (int)addrResult->ai_addrlen);
	if (res == SOCKET_ERROR) {
		#if XELANETWORK_DEBUG_SERVER
		std::cout << "[XelaServer] Failed to bind socket: " << WSAGetLastError() << std::endl;
		#endif
		freeaddrinfo(addrResult);
		closesocket(s->listenSock);
		s->isOpen = false;
		return XELANETWORK_ERROR_BIND_SOCKET;
	}
	freeaddrinfo(addrResult);

	return XELANETWORK_SUCCESS;
}
#endif