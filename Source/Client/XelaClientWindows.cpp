#include "XelaClient.h"

#include <string>

#if defined(_WIN32)
void xelaSetupClientHints(addrinfo *hints, int protocol) {
	ZeroMemory(hints, sizeof(*hints));
	hints->ai_family = AF_UNSPEC;		//Can be IPv4 or IPv6

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

XelaSocket *XelaClient::initWindows(char *ip, char *port, addrinfo *hints, SOCKET *connectSock, bool *open, int protocol, int *success) {
	addrinfo *addrResult;

	xelaSetupClientHints(hints, protocol);

	#if XELANETWORK_DEBUG_CLIENT
	std::cout << "[XelaClient] Creating new Xela Client" << std::endl;
	std::cout << "[XelaClient] ===| Protocol: " << (protocol == XELANETWORK_PROTO_TCP ? "TCP" : protocol == XELANETWORK_PROTO_UDP ? "UDP" : "Other") << std::endl;
	#endif

	int res = getaddrinfo(ip, port, hints, &addrResult);
	if (res != 0) {
		#if XELANETWORK_DEBUG_CLIENT
		std::cout << "[XelaClient] Error at getaddrinfo: " << WSAGetLastError() << std::endl;
		#endif
		*open = false;
		*success = XELANETWORK_ERROR_GETADDRINFO;
		return nullptr;
	}

	*connectSock = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
	if (*connectSock == INVALID_SOCKET) {
		#if XELANETWORK_DEBUG_CLIENT
		std::cout << "[XelaClient] Error calling socket(): " << WSAGetLastError() << std::endl;
		#endif
		freeaddrinfo(addrResult);
		*open = false;
		*success = XELANETWORK_ERROR_CREATE_SOCKET;
		return nullptr;
	}

	#if XELANETWORK_DEBUG_CLIENT
	std::cout << "[XelaClient] Connecting to " << ip << ":" << port << std::endl;
	#endif

	if (protocol == XELANETWORK_PROTO_TCP) {
		*success = XelaClient::connectTCPWindows(ip, port, addrResult, connectSock, open);
		if (*success != XELANETWORK_SUCCESS) {
			return nullptr;
		}
	}

	*success = XELANETWORK_SUCCESS;

	XelaSocket *newSock = XelaSocket::genSocket(*connectSock, protocol, ip, (unsigned short)std::stoi(port));
	return newSock;
}
#endif