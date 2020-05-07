#include "XelaSocket.h"

#include <string.h>

#if defined(_WIN32)
void XelaSocket::write_platformTCP(XelaSocket *s, char *msg, int msgLen) {
	int result = send(s->connection, msg, msgLen, 0);

	if (result == SOCKET_ERROR) {
		#if XELANETWORK_DEBUG_SOCKET
		std::cout << "[XelaSocket] Error sending message: " << msg << ": " << WSAGetLastError() << std::endl;
		#endif
	}
}

void XelaSocket::get_platformTCP(XelaSocket *s, char **buf, int bufLen, int *resLen, char **ip, char **port) {
	*resLen = recv(s->connection, *buf, bufLen, 0);

	if (resLen < 0) {
		#if XELANETWORK_DEBUG_SOCKET
		std::cout << "[XelaSocket] Error recieving message: " << WSAGetLastError() << std::endl;
		#endif
	}

	if (ip != nullptr) {
		strncpy_s(*ip, IPV4_STRLEN, s->ip, IPV4_STRLEN);
	}
	if (port != nullptr) {
		strncpy_s(*port, IPV4_STRLEN, s->port, IPV4_STRLEN);
	}
}
#endif