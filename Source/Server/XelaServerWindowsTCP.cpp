#include "XelaServer.h"

#include <iostream>

#if defined(_WIN32)
XelaSocket *XelaServer::acceptTCPWindows(SOCKET sock, bool *open, int protocol, bool listening, int *success) {
	if (!listening) {
		if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
			#if XELANETWORK_DEBUG_SERVER
			std::cout << "[XelaServer] Error listening with socket: " << WSAGetLastError() << std::endl;
			#endif
			closesocket(sock);
			*open = false;
			*success = XELANETWORK_ERROR_LISTEN_SOCKET;
			return nullptr;
		}
	}

	#if XELANETWORK_DEBUG_SERVER
	std::cout << "[XelaServer] Attempting to accept a connection" << std::endl;
	#endif
	SOCKET newClient = INVALID_SOCKET;

	//Accept new client
	newClient = accept(sock, NULL, NULL);
	if (newClient == INVALID_SOCKET) {
		#if XELANETWORK_DEBUG_SERVER
		std::cout << "[XelServer] Error accepting connection: " << WSAGetLastError() << std::endl;
		#endif
		closesocket(sock);
		*open = false;
		*success = XELANETWORK_ERROR_ACCEPT_CONNECTION;
		return nullptr;
	}

	SOCKADDR_IN client = { 0 };
	int len = sizeof(SOCKADDR_IN);
	getpeername(newClient, (sockaddr *)&client, &len);

	char *ip = new char[IPV4_STRLEN];
	sprintf_s(ip, IPV4_STRLEN, "%d.%d.%d.%d", client.sin_addr.S_un.S_un_b.s_b1, client.sin_addr.S_un.S_un_b.s_b2, client.sin_addr.S_un.S_un_b.s_b3, client.sin_addr.S_un.S_un_b.s_b4);

	#if XELANETWORK_DEBUG_SERVER
	std::cout << "[XelaServer] Accepted new connection" << std::endl;
	#endif

	*success = XELANETWORK_SUCCESS;
	XelaSocket *newSock = XelaSocket::genSocket(newClient, protocol, ip, ntohs(client.sin_port));
	return newSock;
}
#endif