all: server player

server: server.o networking.o
	gcc -o server server.o networking.o

player: player.o networking.o
	gcc -o player player.o networking.o

player.o: player.c networking.h
	gcc -c player.c

server.o: server.c networking.h
	gcc -c server.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
