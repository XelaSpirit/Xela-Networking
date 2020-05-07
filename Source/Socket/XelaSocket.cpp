#include "XelaSocket.h"

void XelaSocket::closeSocket(XelaSocket *s) {
	XelaSocket::close_platform(s);
}
void XelaSocket::write(XelaSocket *s, char *msg, int msgLen, char *toIp, char *toPort) {
	switch (s->proto) {
		case XELANETWORK_PROTO_TCP:
			XelaSocket::write_platformTCP(s, msg, msgLen);
			break;
		case XELANETWORK_PROTO_UDP:
			XelaSocket::write_platformUDP(s, msg, msgLen, (toIp == nullptr ? s->ip : toIp), (toPort == nullptr ? s->port : toPort));
			break;
	}
}

void XelaSocket::get(XelaSocket *s, char **buf, int bufLen, int *resLen, char **fromIp, char **fromPort) {
	switch (s->proto) {
		case XELANETWORK_PROTO_TCP:
			return XelaSocket::get_platformTCP(s, buf, bufLen, resLen, fromIp, fromPort);
			break;
		case XELANETWORK_PROTO_UDP:
			return XelaSocket::get_platformUDP(s, buf, bufLen, resLen, fromIp, fromPort);
			break;
	}
}