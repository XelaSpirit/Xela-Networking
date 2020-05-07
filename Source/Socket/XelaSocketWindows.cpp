#include "XelaSocket.h"

#include <iostream>

#if defined(_WIN32)
XelaSocket *XelaSocket::genSocket(SOCKET c, int protocol, char *connectIp, unsigned short connectPort) {
	XelaSocket *ret = new XelaSocket();
	ret->connection = c;
	ret->proto = protocol;
	ret->port = new char[6];
	sprintf_s(ret->port, 6, "%d", (int)connectPort);
	if (connectIp != nullptr) {
		ret->ip = new char[16];
		strcpy_s(ret->ip, 16, connectIp);
	}

	return ret;
}
void XelaSocket::close_platform(XelaSocket *s) {
	int result = shutdown(s->connection, SD_BOTH);
	if (result == SOCKET_ERROR) {
		#if XELANETWORK_DEBUG_SOCKET
		std::cout << "[XelaSocket] Error on socket shutdown: " << WSAGetLastError() << std::endl;
		#endif
	}
	closesocket(s->connection);
	s->isOpen = false;
}
void XelaSocket::waitForData(XelaSocket *s) {
	FD_SET set;
	FD_ZERO(&set);
	FD_SET(s->connection, &set);
	int t = select(0, &set, NULL, NULL, NULL);
}
bool XelaSocket::hasGet(XelaSocket *s, long timeoutSec, long timeoutMicroSec) {
	FD_SET set;
	FD_ZERO(&set);
	FD_SET(s->connection, &set);
	TIMEVAL time = { timeoutSec, timeoutMicroSec };
	int t = select(0, &set, NULL, NULL, &time);
	return (t > 0);
}
#endif