#include "XelaClient.h"

#if defined(_WIN32)
int XelaClient::connectTCPWindows(char *ip, char *port, addrinfo *addrResult, SOCKET *connectSock, bool *open) {
	int res = connect(*connectSock, addrResult->ai_addr, (int)addrResult->ai_addrlen);
	while (res == SOCKET_ERROR) {
		if (addrResult->ai_next == nullptr) {
			#if XELANETWORK_DEBUG_CLIENT
			std::cout << "[XelaClient] Error connecting to " << ip << ":" << port << ": " << WSAGetLastError() << std::endl;
			#endif
			closesocket(*connectSock);
			*open = false;
			return XELANETWORK_ERROR_CONNECT_SOCKET;
		}
		else {
			addrResult = addrResult->ai_next;
			res = connect(*connectSock, addrResult->ai_addr, (int)addrResult->ai_addrlen);
		}
	}
	while (*connectSock == INVALID_SOCKET) {
		if (addrResult->ai_next == nullptr) {
			#if XELANETWORK_DEBUG_CLIENT
			std::cout << "[XelaClient] Error connecting to " << ip << ":" << port << ": " << WSAGetLastError() << std::endl;
			#endif
			closesocket(*connectSock);
			*open = false;
			return XELANETWORK_ERROR_CONNECT_SOCKET;
		}
		else {
			addrResult = addrResult->ai_next;
			res = connect(*connectSock, addrResult->ai_addr, (int)addrResult->ai_addrlen);
		}
	}
	return XELANETWORK_SUCCESS;
}
#endif