#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd < 0) {
    perror("socket");
    exit(-1);
  }

  struct sockaddr_in fd_adr;
  fd_adr.sin_family = AF_INET;
  fd_adr.sin_port = htons(8080);
  fd_adr.sin_addr.s_addr = INADDR_ANY;

  if(bind(fd, (struct sockaddr*)&fd_adr, sizeof(fd_adr)) < 0) {
    perror("bind");
    exit(-1);
  }
  if(listen(fd, 5) < 0) {
    perror("listen");
    exit(-1);
  }

  while(1) {
    int client_fd = accept(fd, NULL, NULL);
    if(client_fd < 0) {
      perror("Client fd");
      exit(-1);
    }
    printf("Connection found: %d\n", client_fd);

    char buff[256];
    int n;
    while((n = (int)read(client_fd, buff, sizeof(buff))) > 0) {
      write(client_fd, buff, n);
    }

    close(client_fd);
    printf("Disconected\n");
  }

  return 0;
}
