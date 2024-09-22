# A simple IPv6 distributed application

## Description

The files in this folder implement a very simple IPv6 distributed
application consisting of a server and one or more clients.

### Server

Once started, the server runs until it is aborted (`control-c`).  The
server waits for incoming requests and replies with a unique number.
By default, the server listens on all the local interfaces (`::`).  If
passed an argument, the server will listen on the specified interface.
The interface can be identified by its name or its IPv6 address.

```
./server6 localhost
```

The current implementation of the server does not permit changing the
port number dynamically (instead it is fixed to 2000 at compile-time).
The server also repeatedly (every second) prints to the console the
unique number it will serve on the next request.

### Client

The client code sends a single request to the server, prints the
unique number that it received in reply, and exits.  By default, the
client sends the request to `localhost`.  If passed an argument, the
client will send the request to the specified interface.  The
interface can be identified by its name or its IPv6 address.  Like the
server, the client sends its request on a fixed port (2000).

```
./client6 localhost
```
