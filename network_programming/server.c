#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT "8080"
#define BACKLOG 10

int main() {
  int status;
  struct addrinfo hints;
  struct addrinfo *res;

  memset(&hints, 0, sizeof(hints)); // zero out the struct
  hints.ai_family = AF_UNSPEC;      // don't care if it is ipv4 or ipv6
  hints.ai_socktype = SOCK_STREAM;  // use TCP stream sockets
  hints.ai_flags = AI_PASSIVE;      // fill in my IP for me

  if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }
  int socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (socketfd == -1) {
    perror("socket:");
    freeaddrinfo(res);
    exit(1);
  }
  int reuse = 1;
  if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse) ==
      -1) {
    perror("setsockopt:");
    freeaddrinfo(res);
    exit(1);
  }
  if (bind(socketfd, res->ai_addr, res->ai_addrlen) != 0) {
    perror("bind:");
    freeaddrinfo(res);
    exit(1);
  }

  printf("Listening\n");
  if (listen(socketfd, BACKLOG) == -1) {
    perror("listen:");
    freeaddrinfo(res);
    exit(1);
  }

  struct sockaddr_storage incoming_addr;
  socklen_t addr_size = sizeof incoming_addr;
  int connection_fd;

  connection_fd =
      accept(socketfd, (struct sockaddr *)&incoming_addr, &addr_size);
  if (connection_fd == -1) {
    perror("accept:");
    freeaddrinfo(res);
    exit(1);
  }
  char buf[1024];
  int buff_len = 1024;
  int read = recv(connection_fd, buf, buff_len, 0);
  if (read == 0 || read == -1) {
    perror("recv:");
    freeaddrinfo(res);
    exit(1);
  }
  printf("Got %d bytes of data from sucketh: %s", read, buf);
  char *msg = "sucketh deez nuts";
  int len = strlen(msg), sent;
  sent = send(connection_fd, msg, len, 0);
  if (sent != len) {
    printf("Could not send all the data\n");
  } else {
    printf("Sent everyuthing baybeee\n");
  }

  freeaddrinfo(res);
  return 0;
}
