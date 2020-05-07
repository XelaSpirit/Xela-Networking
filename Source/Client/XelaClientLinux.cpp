#include "XelaClient.h"

#include <string>
#include <string.h>

#if defined(__linux__)
XelaSocket *XelaClient::initLinux(char *ip, char *port, int *sockfd, sockaddr_in *serverAddr, hostent **server, bool *open, int protocol, int *success) {
    int portno = atoi((const char *)port);

    //Create socket
    *sockfd = socket(AF_INET, (protocol == XELANETWORK_PROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, 0);
    if (*sockfd < 0) {
        #if XELANETWORK_DEBUG_CLIENT
        std::cout << "[XelaClient] Error creating socket" << std::endl;
        #endif
        *open = false;
        *success = XELANETWORK_ERROR_CREATE_SOCKET;
        return nullptr;
    }

    //Retrieve server information
    *server = gethostbyname(ip);
    if (*server == NULL) {
        #if XELANETWORK_DEBUG_CLIENT
        std::cout << "[XelaClient] Error retrieving host: " << ip << std::endl;
        #endif
        *success = XELANETWORK_ERROR_GETADDRINFO;
        return nullptr;
    }

    //Setup serverAddr
    bzero((char *)serverAddr, sizeof(sockaddr_in));
    serverAddr->sin_family = AF_INET;
    inet_pton(AF_INET, (*server)->h_addr_list[0], &serverAddr->sin_addr.s_addr);
    serverAddr->sin_port = htons(portno);

    if (protocol == XELANETWORK_PROTO_TCP) {
        *success = XelaClient::connectTCPLinux(sockfd, serverAddr, ip, port);
        if (*success != XELANETWORK_SUCCESS) {
            return nullptr;
        }
    }

    *success = XELANETWORK_SUCCESS;
    
    XelaSocket *newSock = XelaSocket::genSocket(*sockfd, protocol, ip, port);
    return newSock;
}
#endif