#include "XelaServer.h"
#include "XelaNetworkInit.h"

XelaServer *XelaServer::genServer(char *port, int protocol, int *success) {
	XelaServer *ret = new XelaServer();
	if (!xelaNetworkingInit()) {
		*success = XELANETWORK_ERROR_INIT;
		ret->isOpen = false;
	}
	else {
		*success = XelaServer::init_platform(ret, port, protocol);
	}
	ret->proto = protocol;

	return ret;
}

XelaSocket *XelaServer::listenServer(XelaServer *s, int *success) {
	switch (s->proto) {
		case XELANETWORK_PROTO_TCP:
			#if defined(_WIN32)
			return XelaServer::acceptTCPWindows(s->listenSock, &s->isOpen, s->proto, s->listening, success);
			#elif defined(__linux__)
			return XelaServer::acceptTCPLinux(s->sockfd, &s->isOpen, s->proto, s->listening, success);
			#endif
			s->listening = true;
			break;
		case XELANETWORK_PROTO_UDP:
			#if defined(_WIN32)
			return XelaServer::listenUDPWindows(s->listenSock, &s->isOpen, s->proto, success);
			#elif defined(__linux__)
			return XelaServer::listenUDPLinux(s->sockfd, &s->isOpen, s->proto, success);
			#endif
			break;
			s->listening = true;
	}

	*success = XELANETWORK_ERROR_INVALID_PROTOCOL;
	return nullptr;
}