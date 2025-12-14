#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("Connect");
    exit(EXIT_FAILURE);
  }
    
  char buff[512];
  int n;
  while((n = (int)read(STDIN_FILENO, buff, sizeof(buff))) > 0) { 
    if(n >= 4 && !memcmp(buff, "quit", 4)) {
      break;
    }
    write(STDOUT_FILENO, "> ", 2);
    write(sock, buff, n);

    int r = read(sock, buff, sizeof(buff));
    if(r > 0) printf("%s", buff);
  }

  close(sock);
}

