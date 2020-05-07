#include "XelaClient.h"

#if defined(__linux__)
int XelaClient::connectTCPLinux(int *sockfd, sockaddr_in *serverAddr, char *ip, char *port) {
    //Connect to the server
    if (connect(*sockfd, (sockaddr *)serverAddr, sizeof(sockaddr_in)) < 0) {
        #if XELANETWORK_DEBUG_CLIENT
        std::cout << "[XelaClient] Error connecting to server " << ip << ":" << port << std::endl;
        #endif
        return XELANETWORK_ERROR_CONNECT_SOCKET;
    }

    return XELANETWORK_SUCCESS;
}
#endif