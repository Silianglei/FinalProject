all: server.o player.o question.o
	gcc -o program server.o player.o question.o

client.o: client.c
	gcc -c client.c

server.o: server.c server.h
	gcc -c server.c

player.o: player.c player.h
	gcc -c player.c

question.o: question.c question.h
	gcc -c question.c

run:
	./program

clean:
	rm *.o
	rm program
