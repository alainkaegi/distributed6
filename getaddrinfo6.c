#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "getaddrinfo6.h"

int getaddrinfo6(char *host, in_port_t port, struct addrinfo **addrinfo) {
    // Translate port number to a string
    // Port is a 16-bit quantity (maximum 65535 or at most 5
    // characters) plus terminating NUL character
    char port_string[6];
    snprintf(port_string, sizeof(port_string), "%d", port);

    // Narrow the search to an IPv6 address usable with UDP
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;         // IPv6 only
    hints.ai_socktype = SOCK_DGRAM;     // datagram socket
    hints.ai_protocol = IPPROTO_UDP;    // UDP

    // Get the IPv6 address
    return getaddrinfo(host, port_string, &hints, addrinfo);
}
