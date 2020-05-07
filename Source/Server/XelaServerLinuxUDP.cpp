#include "XelaServer.h"

#if defined(__linux__)
XelaSocket *XelaServer::listenUDPLinux(int sockfd, bool *open, int protocol, int *success) {
	//Start listening for data
	*success = XELANETWORK_SUCCESS;

	XelaSocket *newSock = XelaSocket::genSocket(sockfd, protocol, nullptr, nullptr);
	return newSock;
}
#endif
