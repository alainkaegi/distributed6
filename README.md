# A simple IPv6 distributed application

## Description

The files in this folder implement the [Echo
Protocol](https://en.wikipedia.org/wiki/Echo_Protocol) with IPv6.

## Requirements

* POSIX
* C build tools

## Build

To build the binaries, simply type

```
make
```

## Server

To start the server, type

```
./server6
```

Once started, the server runs until it is aborted (`control-c`).  The
server waits for incoming requests and replies with the same content
as those requests (up to 2048 bytes per request).

By default, the server listens on all the local interfaces at port
2000 (the original protocol used port 7 but selecting that port requires
root privilege).

The server also repeatedly (every second) prints to the console the
number of requests it has seen so far.

The server supports a limited set of command-line arguments.  See below.

### Client

To invoke the client, type

```
./client6
```

The client code sends a single request to the server, prints the reply
(interpreting it as a string of characters), and exits.

By default, the client sends the request to `localhost` port 2000.

The client supports a limited set of arguments.  See below.

## Command-line arguments

The server and the client accept up to two optional arguments.  The
first argument specifies an alternate interface.  The interface can be
identified by its name or its IPv6 address.  The second argument
specifies an alternate port.

Below are a few examples:

```
./client6 localhost
./client6 ::1 2000
```
