#include <xela/networking/XelaClient.h>
#include <xela/networking/XelaSocket.h>

#include <iostream>

int main() {
    int suc = 0;
    XelaClient *client = XelaClient::genClient(XELANETWORK_PROTO_TCP, &suc);
    if (suc != XELANETWORK_SUCCESS) {
        std::cout << "ERROR: " << suc << std::endl;
        return 1;
    }

    XelaSocket *sock = XelaClient::connectClient(client, (char *)"127.0.0.1", (char *)"64355", &suc);
    if (suc != XELANETWORK_SUCCESS) {
        std::cout << "ERROR: " << suc << std::endl;
        return 1;
    }

    XelaSocket::write(sock, (char *)"Hello!", 7);

    char *buf = new char[7];
    int resLen = 0;
    XelaSocket::get(sock, &buf, 7, &resLen);

    std::cout << resLen << " characters." << std::endl;
    std::cout << "Message: " << buf << std::endl;

    XelaSocket::closeSocket(sock);

    return 0;
}