#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>

void *handle_connection(void *arg) {
  int client_fd = *(int*)arg;

   char buff[512];
    int n;
    while((n = (int)read(client_fd, buff, sizeof(buff))) > 0) {
      write(client_fd, buff, n);
      dprintf(STDOUT_FILENO, "Client: %d; write: %s\n", client_fd, buff);
    }

    close(client_fd);
    printf("Disconnected\n");
    return NULL;
}

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
    pthread_t t;
    int client_fd = accept(fd, NULL, NULL);
    if(client_fd < 0) {
      perror("Client fd");
      exit(-1);
    }
    printf("Connection found: %d\n", client_fd);

    int *pdf = malloc(sizeof(int));
    *pdf = client_fd;

    pthread_create(&t, NULL, handle_connection, pdf);

    pthread_detach(t);

    free(pdf);
  }

  return 0;
}
