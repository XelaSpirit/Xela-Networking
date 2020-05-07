#include "XelaServer.h"

#if defined(_WIN32)
XelaSocket *XelaServer::listenUDPWindows(SOCKET sock, bool *open, int protocol, int *success) {
	//Accept new clients
	*success = XELANETWORK_SUCCESS;

	XelaSocket *newSock = XelaSocket::genSocket(sock, protocol, nullptr, 0);
	return newSock;
}
#endif