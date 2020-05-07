#include "XelaSocket.h"

#include <string>

#if defined(_WIN32)
void XelaSocket::write_platformUDP(XelaSocket *s, char *msg, int msgLen, char *ip, char *port) {
	SOCKADDR_IN sendAddr;
	sendAddr.sin_family = AF_INET;
	sendAddr.sin_port = htons((unsigned short)std::stoi(port));

	int res = inet_pton(AF_INET, ip, &sendAddr.sin_addr);
	if (res != 1) {
		if (res == 0) {
			#if XELANETWORK_DEBUG_SOCKET
			std::cout << "[XelaSocket] Error getting sendto address: Invalid address" << std::endl;
			#endif
		}
		else {
			#if XELANETWORK_DEBUG_SOCKET
			std::cout << "[XelaSocket] Error getting sendto address: " << WSAGetLastError() << std::endl;
			#endif
		}
	}

	int flags = 0;
	res = sendto(s->connection, msg, msgLen, flags, (SOCKADDR *)&sendAddr, sizeof(sendAddr));

	if (res == SOCKET_ERROR) {
		#if XELANETWORK_DEBUG_SOCKET
		std::cout << "[XelaSocket] Error sending message: " << WSAGetLastError() << std::endl;
		#endif
		return;
	}
}

void XelaSocket::get_platformUDP(XelaSocket *s, char **buf, int bufLen, int *resLen, char **ip, char **port) {
	//Recieve message
	int flags = 0;
	SOCKADDR_IN from;
	int from_size = sizeof(from);
	*resLen = recvfrom(s->connection, *buf, bufLen, flags, (SOCKADDR *)&from, &from_size);

	if (*resLen == SOCKET_ERROR) {
		#if XELANETWORK_DEBUG_SOCKET
		std::cout << "[XelaSocket] Error recieving message: " << WSAGetLastError() << std::endl;
		#endif
	}

	if (ip != nullptr) {
		sprintf_s(*ip, IPV4_STRLEN, "%d.%d.%d.%d", (int)from.sin_addr.S_un.S_un_b.s_b1, (int)from.sin_addr.S_un.S_un_b.s_b2, (int)from.sin_addr.S_un.S_un_b.s_b3, (int)from.sin_addr.S_un.S_un_b.s_b4);
		(*ip)[15] = '\0';
	}
	if (port != nullptr) {
		sprintf_s(*port, PORT_STRLEN, "%d", (int)ntohs(from.sin_port));
		(*port)[5] = '\0';
	}
}
#endif