all: server player

server: server.o networking.o question.o
	gcc -o server server.o networking.o question.o

player: player.o networking.o
	gcc -o player player.o networking.o

player.o: player.c networking.h
	gcc -c player.c

server.o: server.c networking.h question.h player.h
	gcc -c server.c

networking.o: networking.c networking.h
	gcc -c networking.c

question.o: question.c question.h
	gcc -c question.c

clean:
	rm *.o
	rm *~
