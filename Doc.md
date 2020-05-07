# Xela Networking Documentation

#### Version 1.0.0
#### 5 / 2 / 2020
#### Author: Alex Morse

## Table of Contents
* [XelaNetworking.h](#xelanetworkingh)
  * [Errors](#errors)
  * [Protocols](#protocols)
  * [Data](#data)
* [XelaServer.h](#xelaserverh)
  * [Struct XelaServer](#struct-xelaserver)
    * [genServer()](#genserver)
    * [listenServer()](#listenserver)
* [XelaClient.h](#xelaclienth)
  * [Struct XelaClient](#struct-xelaclient)
    * [genClient()](#genclient)
    * [connectClient()](#connectclient)
* [XelaSocket.h](#xelasocketh)
  * [Struct XelaSocket](#struct-xelasocket)
    * [closeSocket()](#closesocket)
    * [write()](#write)
    * [get()](#get)
    * [waitForData()](#waitfordata)
    * [hasGet()](#hasget)

## XelaNetworking.h
### Errors
```C++
#define XELANETWORK_SUCCESS 0
```
Indicates that a function executed successfully.
<br><br>

```C++
#define XELANETWORK_ERROR_INIT 1
```
Indicates that there was a problem initializing XelaNetworking.
<br><br>

```C++
#define XELANETWORK_ERROR_GETADDRINFO 2
```
Indicates that there was a problem getting ip address info.
<br><br>

```C++
#define XELANETWORK_ERROR_CREATE_SOCKET 3
```
Indicates that there was a problem creating a socket.
<br><br>

```C++
#define XELANETWORK_ERROR_BIND_SOCKET 4
```
Indicates that there was a problem binding a socket.
<br><br>

```C++
#define XELANETWORK_ERROR_LISTEN_SOCKET 5
```
Indicates that there was a problem listening for data on a socket.
<br><br>

```C++
#define XELANETWORK_ERROR_ACCEPT_CONNECTION 6
```
Indicates that there was a problem accepting connections on a socket.
<br><br>

```C++
#define XELANETWORK_ERROR_CONNECT_SOCKET 7
```
Indicates that there was a problem connecting to another computer with a socket.

```C++
#define XELANETWORK_ERROR_INVALID_PROTOCOL 8
```
Indicates that the protocol given is not recognized by XelaNetworking.
<br><br><br><br>

### Protocols
```C++
#define XELANETWORK_PROTO_TCP 0
```
Definition for [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) network protocol.
<br><br>

```C++
#define XELANETWORK_PROTO_UDP 1
```
Definition for [UDP](https://en.wikipedia.org/wiki/User_Datagram_Protocol) network protocol.
<br><br><br><br>

### Data
```C++
#define IPV4_STRLEN 16
```
How long a string containing an IPv4 address should be. Functions that return an IPv4 address expect buffers to be initialized with this length.
<br><br>

```C++
#define PORT_STRLEN 6
```
How long a string containing a port should be. Functions that return a port number as a string expect buffers to be initialized with this length.
<br><br><br><br>

## XelaServer.h
### Struct XelaServer
Struct containing data/functions for creating servers and accepting client connections.
<br><br>

#### genServer()
```C++
static XELANETWORK_API XelaServer *genServer(char *port, int protocol, int *success);
```
Creates a new XelaServer that listens on a given port and uses a given protocol, then returns a pointer to that XelaServer.

Port should be a string representing the port number for the server to listen on, such as "25565".

Protocol should be one of XELANETWORK_PROTO_TCP or XELANETWORK_PROTO_UDP.

On success, success is set to XELANETWORK_SUCCESS.

If XelaNetworking wasn't already initialized, and fails to do so, success is set to XELANETWORK_ERROR_INIT.

If this function fails to get ip address info using the given port, success is set to XELANETWORK_ERROR_GETADDRINFO.

If this function fails to create a socket using the given port, success is set to XELANETWORK_ERROR_CREATE_SOCKET.

If this funtion fails to bind a socket to the given port, success is set to XELANETWORK_ERROR_BIND_SOCKET
<br><br>

#### listenServer()
```C++
static XELANETWORK_API XelaSocket *listenServer(XelaServer *s, int *success);
```
If s is using XELANETWORK_PROTO_TCP this function will wait for a new client to connect, then accept that connection and create a new XelaSocket for communication with that client. This function will return a pointer to the newly generated XelaSocket.

If s is using XELANETWORK_PROTO_UDP this function will create a new XelaSocket to accept all data sent by clients to this server. This function will return a pointer to the newly generated XelaSocket.

success is set to XELANETWORK_SUCCESS on a success.

success is set to XELANETWORK_ERROR_LISTEN_SOCKET if there's a problem listening for connection requests on the server.

success is set to XELANETWORK_ERROR_ACCEPT_CONNECTION if there's a problem accepting a client's connection request.

Success is set to XELANETWORK_ERROR_INVALID_PROTOCOL if the protocol used by s is unrecognized.
<br><br><br><br>

## XelaClient.h
### Struct XelaClient
Struct containing data/functions for creating clients and connecting to servers.
<br><br>

#### genClient()
```C++
static XELANETWORK_API XelaClient *genClient(int protocol, int *success);
```
Creates a new XelaClient for connecting to a server with a given protocol and returns a pointer to it. Protocol can be one of XELANETWORK_PROTO_TCP or XELANETWORK_PROTO_UDP.

Success is set to XELANETWORK_SUCCESS if this succeeds.

Success is set to XELANETWORK_ERROR_INIT if XelaNetworking wasn't already initialized, and fails to do so.
<br><br>

#### connectClient()
```C++
static XELANETWORK_API XelaSocket *connectClient(XelaClient *c, char *ip, char *port, int *success);
```
Connects to a server at ip:port, then generates a new XelaSocket to handle communication with the server. This function returns a pointer to the newly created XelaSocket.

success is set to XELANETWORK_SUCCESS if the client connects successfully.

success is set to XELANETWORK_ERROR_GETADDRINFO if there's a problem getting information about the ip address and port.

success is set to XELANETWORK_ERROR_CREATE_SOCKET if there's a problem creating a socket with the ip address and port.
<br><br><br><br>

## XelaSocket.h
### Struct XelaSocket
Struct containing data/functions for communication between clients/servers.

This struct is automatically created by either XelaServer or XelaClient upon a connection being formed.
<br><br>

#### closeSocket()
```C++
static XELANETWORK_API void closeSocket(XelaSocket *s);
```
Closes the socket and prevents any further communication with it.
<br><br>

#### write()
```C++
static XELANETWORK_API void write(XelaSocket *s, char *msg, int msgLen, char *toIp = nullptr, char *toPort = nullptr);
```
Sends a message to the socket s is connected to.

If toIp/toPort are specified, will send to that ip/port. Otherwise, the ip and port given when s was created will be used. If this socket was created by a XelaClient, ip and port will already be set to the server this socket is connected to. If this socket was created by a XelaServer, ip and port will only be set if the server is using the TCP protocol, otherwise toIp and toPort need to be specified here.
<br><br>

#### get()
```C++
static XELANETWORK_API void get(XelaSocket *s, char **buf, int bufLen, int *resLen, char **fromIp = nullptr, char **fromPort = nullptr);
```
Returns the next message recieved by this socket as a string.

If fromIp/fromPort are specified, they will be set to the ip/port of the computer that sent the message.

The message will be stored in the char array pointed to by buf, which should already be initialized to be at least bufLen characters long.

The int pointed to by resLen will be set to the length of the message recieved.

If fromIp and fromPort are being used, the char arrays they point to should already be initialized to IPV4_STRLEN and PORT_STRLEN characters long, respectively.
<br><br>

#### waitForData()
```C++
static XELANETWORK_API void waitForData(XelaSocket *s);
```
Pauses execution of the thread this is called from until a message is available to be read on s.
<br><br>

#### hasGet()
```C++
static XELANETWORK_API bool hasGet(XelaSocket *s, long timeoutSec = 0, long timeoutMicroSec = 0);
```
Waits at most timeoutSec seconds and timeoutMicroSec microseconds and returns true if s has a message that can be read, and returns false otherwise. If timeoutSec and timeoutMicrosec are both set to 0, will return an answer immediately.
<br><br>