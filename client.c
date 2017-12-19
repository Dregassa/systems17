#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;
  char buffer[BUFFER_SIZE];

  from_server = client_handshake( &to_server );

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(to_server, buffer, BUFFER_SIZE);
    read(from_server, buffer, BUFFER_SIZE);
    printf("received: [%s]\n", buffer);
  }
}
