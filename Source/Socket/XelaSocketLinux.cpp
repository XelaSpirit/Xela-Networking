#include "XelaSocket.h"

#if defined(__linux__)
XelaSocket *XelaSocket::genSocket(int fd, int protocol, char *connectIp, char *connectPort) {
    XelaSocket *ret = new XelaSocket();
    ret->sockfd = fd;
    ret->proto = protocol;
    ret->ip = connectIp;
    ret->port = connectPort;

    return ret;
}

void XelaSocket::close_platform(XelaSocket *s) {
    shutdown(s->sockfd, SHUT_RD);
    close(s->sockfd);
    s->isOpen = false;
}

void XelaSocket::waitForData(XelaSocket *s) {
    fd_set set;
    FD_ZERO(&set);
    FD_SET(s->sockfd, &set);
    int t = select(0, &set, NULL, NULL, NULL);
}
bool XelaSocket::hasGet(XelaSocket *s, long timeoutSec, long timeoutMicroSec) {
    fd_set set;
    FD_ZERO(&set);
    FD_SET(s->sockfd, &set);
    timeval time = { timeoutSec, timeoutMicroSec };
    int t = select(0, &set, NULL, NULL, &time);
    return (t > 0);
}
#endif