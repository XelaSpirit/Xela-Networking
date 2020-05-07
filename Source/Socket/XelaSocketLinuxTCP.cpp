#include "XelaSocket.h"

#include <string.h>

#if defined(__linux__)
void XelaSocket::write_platformTCP(XelaSocket *s, char *msg, int msgLen) {
    int n = send(s->sockfd, msg, msgLen, 0);

    if (n >= 0) {
        #if XELANETWORK_DEBUG_SOCKET
        std::cout << "[XelaSocket] Sent message: " << msg << std::endl;
        #endif
    }
    else {
        #if XELANETWORK_DEBUG_SOCKET
        std::cout << "[XelaSocket] Error sending message: " << msg << ":" << n << std::endl;
        #endif
    }
}

void XelaSocket::get_platformTCP(XelaSocket *s, char **buf, int bufLen, int *resLen, char **ip, char **port) {
    bzero(*buf, bufLen);
    *resLen = read(s->sockfd, *buf, bufLen);

    if (*resLen >= 0) {
        #if XELANETWORK_DEBUG_SOCKET
        std::cout << "[XelaSocket] Recieved message: " << n << " bytes" << std::endl;
        #endif
    }
    else {
        #if XELANETWORK_DEBUG_SOCKET
        std::cout << "[XelaSocket] Error reading from socket: " << n << std::endl;
        #endif
        return;
    }

    if (ip != nullptr) {
        strncpy(*ip, s->ip, IPV4_STRLEN);
    }
    if (port != nullptr) {
        strncpy(*port, s->port, PORT_STRLEN);
    }
}
#endif