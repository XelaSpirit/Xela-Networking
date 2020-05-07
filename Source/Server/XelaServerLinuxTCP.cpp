#include "XelaServer.h"

#include <string>

#if defined(__linux__)
XelaSocket *XelaServer::acceptTCPLinux(int sockfd, bool *open, int protocol, bool listening, int *success) {
	if (!listening) {
		//Start listening on socket
		int res = listen(sockfd, SOMAXCONN);

		if (res < 0) {
			#if XELANETWORK_DEBUG_SERVER
			std::cout << "[XelaServer] Error listening on socket" << std::endl;
			#endif
			*open = false;
			*success = XELANETWORK_ERROR_LISTEN_SOCKET;
			return nullptr;
		}
	}

	//Accept new client
	sockaddr_in client;
	unsigned int clen = sizeof(sockaddr_in);
	int clientfd = accept(sockfd, (sockaddr *)&client, &clen);
	if (clientfd < 0) {
		#if XELANETWORK_DEBUG_SERVER
		std::cout << "[XelaServer] Error accepting client" << std::endl;
		#endif
		*success = XELANETWORK_ERROR_ACCEPT_CONNECTION;
		return nullptr;
	}

	char *ip = new char[IPV4_STRLEN];
	inet_ntop(AF_INET, &client.sin_addr, ip, IPV4_STRLEN);

	char *port = new char[PORT_STRLEN];
	sprintf(port, "%d", client.sin_port);

	*success = XELANETWORK_SUCCESS;

	XelaSocket *newSock = XelaSocket::genSocket(clientfd, protocol, ip, port);
	return newSock;
}
#endif
