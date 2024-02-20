#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "default_config.h"
#include "getaddrinfo6.h"

static unsigned long ticket = 0;

static void notified() {
    printf("%lu\n", ticket);
}

static void configure_timer() {
    // Create a timer
    struct sigevent sev;
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = &notified;
    sev.sigev_value.sival_ptr = NULL;
    timer_t timer_id;
    if (timer_create(CLOCK_REALTIME, &sev, &timer_id) < 0) {
        perror("server6: timer_create");
        exit(1);
    }

    // Set the timer
    struct itimerspec its = {
        .it_value.tv_sec = 1,
        .it_value.tv_nsec = 0,
        .it_interval.tv_sec = 1,
        .it_interval.tv_nsec = 0
    };
    if (timer_settime(timer_id, 0, &its, NULL) < 0) {
        perror("server6: timer_settime");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    char *host = default_host;
    in_port_t port = default_port;

    // Check for arguments
    if (argc > 1) {
        host = argv[1];
    }

    // Configure a recurring timer
    configure_timer();

    // Get the IPv6 address
    struct addrinfo *addrinfo;
    int s = getaddrinfo6(host, port, &addrinfo);
    if (s != 0) {
        fprintf(stderr,
                "server6: getaddrinfo6: [%s]:%d: %s\n",
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
    printf("server6: Serving requests to [%.50s]:%d\n", buf, port);

    // Get a communication endpoint
    int fd = socket(addrinfo->ai_family,
                    addrinfo->ai_socktype,
                    addrinfo->ai_protocol);
    if (fd < 0) {
        perror("server6: socket");
        exit(1);
    }

    // Bind our address to the socket
    if (bind(fd, addrinfo->ai_addr, addrinfo->ai_addrlen) < 0) {
        perror("server6: bind");
        exit(1);
    }

    // Listen to the socket
    while (1) {
        char request[6];
        struct sockaddr_in6 client_address;
        socklen_t client_address_length = sizeof(client_address); // needed on MacOS

        if (recvfrom(fd,
                     request,
                     sizeof(request),
                     0,
                     (struct sockaddr *)&client_address,
                     &client_address_length) < 0){
            perror("server6: recvfrom");
            exit(1);
        }

        int data = htonl(ticket);
        if (sendto(fd,
                   &data,
                   sizeof(data),
                   0,
                   (struct sockaddr *)&client_address,
                   client_address_length) < 0){
            perror("server6: sendto");
            exit(1);
        }

        ++ticket;
    }

}

