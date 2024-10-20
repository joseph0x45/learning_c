#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: showip <hostname>\n");
    return 1;
  }
  struct addrinfo hints, *res, *p;
  int status;
  char ip_string[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 2;
  }

  printf("Print IP addresses for %s\n\n", argv[1]);

  for (p = res; p != NULL; p = p->ai_next) {
    void *addr;
    char *ip_version;

    if (p->ai_family == AF_INET) {
      struct sockaddr_in *ipv4_info = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4_info->sin_addr);
      ip_version = "IPv4";
    } else {
      struct sockaddr_in6 *ipv6_info = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6_info->sin6_addr);
      ip_version = "IPv6";
    }

    inet_ntop(p->ai_family, addr, ip_string, sizeof ip_string);
    printf("\t%s: %s\n", ip_version, ip_string);
  }
  freeaddrinfo(res);
  return 0;
}
