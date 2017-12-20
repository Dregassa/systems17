#include "pipe_networking.h"
#include <signal.h>
#include <ctype.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("wkp");
    exit(0);
  }
}

int main() {
	signal(SIGINT, sighandler);
	
	int from_client;
	int f;

	while (1){
		from_client = server_setup();
		printf("[server]: forking\n");
		f = fork();
		
		if (f == -1){
			exit(1);
		}
		else if (f == 0){//child
			subserver(from_client);
		}
		else{	
			close(from_client);
		}
		
	}
}

void subserver(int from_client) {//done
	int to_client = server_connect(from_client);
	char buffer[BUFFER_SIZE];

	while ( read(from_client, buffer, BUFFER_SIZE) ){
		printf("[subserver %d]: recieved: %s\n", getpid(), buffer);
		process(buffer);
		write(to_client, buffer, BUFFER_SIZE);
	}
	exit(0);
}

void process(char * s) {//capitalize
	int i;
	int size = strlen(s);

	for(i=0; i<size; i++ ){	
		s[i] = toupper(s[i]);
	}

}
