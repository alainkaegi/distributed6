#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "getaddrinfo6.h"

static char default_host[] = "localhost";

static in_port_t default_port = 2000;

/**
 * The client of a simple distributed application.
 *
 * See the accompanying README.md for more detail.
 *
 * Resources:
 *
 * * man 7 ipv6
 *
 * * Eva M. Castro.  Porting Applications to IPv6 HowTo.
 *   http://long.ccaba.upc.edu/long/045Guidelines/eva/ipv6.html
 *
 * * man 3 getaddrinfo
 *
 * * https://en.wikipedia.org/wiki/Getaddrinfo
 */

static char request[] = "hello\n";
static char reply[2048];

int main(int argc, char *argv[])
{
    char *host = default_host;
    in_port_t port = default_port;

    // Check for arguments
    if (argc > 1) {
        host = argv[1];
    }
    if (argc > 2) {
        port = atoi(argv[2]);
    }

    if (argc > 1) {
        host = argv[1];
    }
    // Get the IPv6 address
    struct addrinfo *addrinfo;
    int s = getaddrinfo6(host, port, &addrinfo);
    if (s != 0) {
        fprintf(stderr,
                "client6: getaddrinfo6: [%s]:%d: %s\n",
                host,
                port,
                gai_strerror(s));
        exit(1);
    }

    // Print the hostname
    char buf[50];
    inet_ntop(addrinfo->ai_family,
              &(((struct sockaddr_in6 *)addrinfo->ai_addr)->sin6_addr),
              buf,
              50);
    printf("client6: Sending a request to [%.50s]:%d\n", buf, port);

    // Get a communication endpoint
    int fd = socket(addrinfo->ai_family,
                    addrinfo->ai_socktype,
                    addrinfo->ai_protocol);
    if (fd < 0) {
        perror("client6: socket");
        exit(1);
    }

    // Send a request
    if (sendto(fd,
               request,
               strlen(request),
               0,
               addrinfo->ai_addr,
               addrinfo->ai_addrlen) < 0) {
        perror("client6: sendto");
        exit(1);
    }

    // Get a reply and print it
    ssize_t size;
    if ((size = recvfrom(fd, &reply, sizeof(reply), 0, NULL, NULL)) < 0) {
        perror("client6: recvfrom");
        exit(1);
    }
    printf("%.*s", (int)size, reply);

    // Clean up and exit
    close(fd);
    freeaddrinfo(addrinfo);
    exit(0);
}
