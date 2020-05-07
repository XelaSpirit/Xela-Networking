#include "XelaSocket.h"

#include <string>

#if defined(__linux__)
void XelaSocket::write_platformUDP(XelaSocket *s, char *msg, int msgLen, char *ip, char *port) {
    int portno = atoi((const char *)port);

    sockaddr_in server;
    server.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server.sin_addr.s_addr);
    server.sin_port = htons(portno);

    int n = sendto(s->sockfd, msg, msgLen, 0, (const sockaddr *)&server, sizeof(sockaddr_in));
    if (n >= 0) {
        #if XELANETWORK_DEBUG_SOCKET
        std::cout << "[XelaSocket] Sent message: " << msg << std::endl;
        #endif
    }
    else {
        #if XELANETWORK_DEBUG_SOCKET
        std::cout << "[XelaSocket] Error sending message: " << msg << ": " << n << std::endl;
        #endif
    }
}

void XelaSocket::get_platformUDP(XelaSocket *s, char **buf, int bufLen, int *resLen, char **ip, char **port) {
    sockaddr_in from;
    unsigned int length = sizeof(sockaddr_in);
    *resLen = recvfrom(s->sockfd, *buf, bufLen, 0, (sockaddr *)&from, &length);

    if (*resLen >= 0) {
        #if XELANETWORK_DEBUG_SOCKET
        std::cout << "[XelaSocket] Recieved message: " << n << " bytes" << std::endl;
        #endif
    }
    else {
        #if XELANETWORK_DEBUG_SOCKET
        std::cout << "[XelaSocket] Error recieving message: " << n << std::endl;
        #endif
        return;
    }

    if (ip != nullptr) {
        inet_ntop(AF_INET, &from.sin_addr, *ip, IPV4_STRLEN);
        (*ip)[IPV4_STRLEN - 1] = '\0';
    }
    if (port != nullptr) {
		snprintf(*port, PORT_STRLEN, "%d", ntohs(from.sin_port));
        (*port)[PORT_STRLEN] = '\0';
    }
}
#endif