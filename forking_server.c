#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

void subserver(int from_client) {
  char input[BUFFER_SIZE];
  int to_client = server_connect(from_client);

  while (read(from_client, input, sizeof(input))) {
    printf("recieved %s from client\n", input);
    process(input);
    printf("modified client input: %s\n", input);
    write(to_client, input, sizeof(input));
    printf("sent modified text to client!\n");
  }
}

void process(char * s) {
  int x = 0;
  while(x< strlen(s)){
    s[x] = s[x] + 1;
    x++;
  }
}

int main(){
  signal(SIGINT, sighandler);

  int from_client;

  printf("server starting\n");

  while(1){
    from_client = server_setup();
    int f = fork();

    if(!f){
      printf("fork successful\n");
      subserver(from_client);
    } else{
     remove("luigi");
     printf("[server] handshake: removed wkp\n");
     close(from_client);
   }
  }
  return 0;
}
