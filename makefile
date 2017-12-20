all: client fserver

fserver: forking_server.o pipe_networking.o
	gcc -o server forking_server.o pipe_networking.o

client: client.o pipe_networking.o
	gcc -o client client.o pipe_networking.o

client.o: client.c pipe_networking.h
	gcc -c client.c

forking_server.o: forking_server.c pipe_networking.h
	gcc -c forking_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm client server
	rm *.o
	rm *~
