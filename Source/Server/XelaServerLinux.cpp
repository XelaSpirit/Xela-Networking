#include "XelaServer.h"

#include <string>
#include <string.h>

#if defined(__linux__)
int XelaServer::init_platform(XelaServer *s, char *port, int protocol) {
	bzero((char *)&s->server, sizeof(sockaddr_in));
	s->portno = atoi(port);

	s->sockfd = socket(AF_INET, (protocol == XELANETWORK_PROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, 0);

	if (s->sockfd < 0) {
		#if XELANETWORK_DEBUG_SERVER
		std::cout << "[XelaServer] Error opening socket" << std::endl;
		#endif
		return XELANETWORK_ERROR_CREATE_SOCKET;
	}

	s->server.sin_family = AF_INET;
	s->server.sin_port = htons(s->portno);
	s->server.sin_addr.s_addr = INADDR_ANY;

	int res = bind(s->sockfd, (sockaddr *)&s->server, sizeof(sockaddr_in));
	if (res < 0) {
		#if XELANETWORK_DEBUG_SERVER
		std::cout << "[XelaServer] Error binding socket" << std::endl;
		#endif
		return XELANETWORK_ERROR_BIND_SOCKET;
	}

	return XELANETWORK_SUCCESS;
}
#endif