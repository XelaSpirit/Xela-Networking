#include <xela/networking/XelaServer.h>
#include <xela/networking/XelaSocket.h>

#include <iostream>

int main() {
	int suc = 0;
	XelaServer *server = XelaServer::genServer((char *)"64355", XELANETWORK_PROTO_TCP, &suc);
	if (suc != XELANETWORK_SUCCESS) {
		std::cout << "ERROR: " << suc << std::endl;
		return 1;
	}

	while (true) {
		XelaSocket *sock = XelaServer::listenServer(server, &suc);
		if (suc != XELANETWORK_SUCCESS) {
			std::cout << "ERROR: " << suc << std::endl;
			return 1;
		}

		char *buf = new char[7];
		char *ip = new char[IPV4_STRLEN], *port = new char[PORT_STRLEN];

		int resLen = 0;
		XelaSocket::get(sock, &buf, 7, &resLen, &ip, &port);

		std::cout << ip << ":" << port << " => " << resLen << " characters." << std::endl;
		std::cout << "==| Message: " << buf << std::endl;

		XelaSocket::write(sock, (char *)"Howdy!", 7, ip, port);
	}

	return 0;
}
