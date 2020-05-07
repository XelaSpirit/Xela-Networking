/*=====================================================================
Xela Networking
Created by: Alex Morse
Version 1.0.0 - 02/29/2020

A simple networking library that wraps the networking function on Windows and Linux to allow for cross-platform network programming.
=====================================================================*/

#ifndef _XELA_NETWORKING_H
#define _XELA_NETWORKING_H

//Define dll/so export/visibility macros
#if defined(_WIN32)
	#if defined(XELANETWORKING_EXPORTS)
		#define XELANETWORK_API __declspec(dllexport)
	#else
		#define XELANETWORK_API __declspec(dllimport)
	#endif
	#define XELANETWORK_HIDDEN
#elif defined(__linux__)
	#if defined(XELANETWORKING_EXPORTS)
		#define XELANETWORK_API __attribute__ ((visibility ("default")))
		#define XELANETWORK_HIDDEN __attribute__ ((visibility ("hidden")))
	#else
		#define XELANETWORK_API
		#define XELANETWORK_HIDDEN
	#endif
#else
	#define XELANETWORK_API
	#define XELANETWORK_HIDDEN
#endif

//Debug definitions
#define XELANETWORK_DEBUG_INIT 0
#define XELANETWORK_DEBUG_SERVER 0
#define XELANETWORK_DEBUG_CLIENT 0
#define XELANETWORK_DEBUG_SOCKET 0

//Include platform-specific networking headers
#if defined(_WIN32)
	#include <WinSock2.h>
	#include <WS2tcpip.h>
	#pragma comment(lib, "Ws2_32.lib")
#elif defined(__linux__)
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <arpa/inet.h>
#endif

//Error definitions
#define XELANETWORK_SUCCESS 0
#define XELANETWORK_ERROR_INIT 1
#define XELANETWORK_ERROR_GETADDRINFO 2
#define XELANETWORK_ERROR_CREATE_SOCKET 3
#define XELANETWORK_ERROR_BIND_SOCKET 4
#define XELANETWORK_ERROR_LISTEN_SOCKET 5
#define XELANETWORK_ERROR_ACCEPT_CONNECTION 6
#define XELANETWORK_ERROR_CONNECT_SOCKET 7
#define XELANETWORK_ERROR_INVALID_PROTOCOL 8

//Protocol definitions
#define XELANETWORK_PROTO_TCP 0
#define XELANETWORK_PROTO_UDP 1

#define IPV4_STRLEN 16
#define PORT_STRLEN 6

#endif