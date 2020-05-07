#include "XelaClient.h"
#include "XelaNetworkInit.h"

XelaClient *XelaClient::genClient(int protocol, int *success) {
	XelaClient *ret = new XelaClient();
	if (!xelaNetworkingInit()) {
		*success = XELANETWORK_ERROR_INIT;
		ret->isOpen = false;
	}
	else {
		*success = XELANETWORK_SUCCESS;
	}
	ret->proto = protocol;

	return ret;
}

XelaSocket *XelaClient::connectClient(XelaClient *c, char *ip, char *port, int *success) {
	#if defined(_WIN32)
	return XelaClient::initWindows(ip, port, &c->hints, &c->connectSock, &c->isOpen, c->proto, success);
	#elif defined(__linux__)
	return XelaClient::initLinux(ip, port, &c->sockfd, &c->serverAddr, &c->server, &c->isOpen, c->proto, success);
	#endif
}