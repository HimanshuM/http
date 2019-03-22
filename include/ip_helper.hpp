#ifndef HTTP__IP_HELPER__
#define HTTP__IP_HELPER__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa);

#endif