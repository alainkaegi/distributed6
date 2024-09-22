# A simple IPv6 distributed application

## Description

The files in this folder implement the [Echo
Protocol](https://en.wikipedia.org/wiki/Echo_Protocol) with IPv6.

### Server

Once started, the server runs until it is aborted (`control-c`).  The
server waits for incoming requests and replies with the exact content
of those requests (up to 2048 bytes per request).  By default, the
server listens on all the local interfaces (`::`).  If passed an
argument, the server will listen on the specified interface.  The
interface can be identified by its name or its IPv6 address.

```
./server6 localhost
```

This implementation does not use the original port number of the Echo
Protocol (port number 7).  Instead, this server listens on port 2000.

The server also repeatedly (every second) prints to the console the
number of requests it has seen so far.

### Client

The client code sends a single request to the server, prints the reply
(interpreting it as a string of characters), and exits.  By default,
the client sends the request to `localhost`.  If passed an argument,
the client will send the request to the specified interface.  The
interface can be identified by its name or its IPv6 address.

```
./client6 ::1
```
