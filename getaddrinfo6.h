#pragma once

/**
 * Get an IPv6 addrinfo structure that can be used with a UDP socket.
 *
 * Given a host name, or IPv6 address, and a port number, this
 * function returns an addrinfo structure that can be used with a UDP
 * socket.
 *
 * Upon failure, this function returns a negative number and a call to
 * gai_strerror will return a string with details about the error.
 *
 * Upon success, the caller must call freeaddrinfo to free the
 * returned result.
 *
 * @param host  a host identified by its name or its IPv6 address
 * @param port  a port number
 * @param addrinfo  return addrinfo structure
 * @return 0 if the call succeeds, a negative value upon failure
 */
int getaddrinfo6(char *host, in_port_t port, struct addrinfo **addrinfo);
