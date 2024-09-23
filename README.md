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

## Running the application with `docker`

Build the server docker image calling it `server6`.

```
docker build -f Dockerfile.server6 -t server6 .
```

Build the client docker image calling it `client6`.

```
docker build -f Dockerfile.client6 -t client6 .
```

Create a network named `ip6net`.

```
docker network create --ipv6 --subnet 2001:0DB8::/112 ip6net
```

Start the server.

```
docker run --rm --network ip6net --network-alias server6 server6
```

Run the client.

```
docker run --rm --network ip6net --network-alias client6 client6
```

## Cleanup

Kill the server (you will need its containder ID).

```
docker kill CONTAINER_ID
```

Tear down the network.

```
docker network rm ip6net
```

## Debug

I find the following commands useful.

Start an image and get a shell without running the "CMD".

```
docker run -it --entrypoint /bin/bash server6 -s
```

Get a shell into a running container.

```
docker exec -it CONTAINER_ID /bin/bash
```

List all containers.

```
docker ps -a
```

Remove a container.

```
docker rm CONTAINER_ID
```
