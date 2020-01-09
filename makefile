forking: player fserver

select: splayer sserver

sserver: select_server.o networking.o
	gcc -o server select_server.o networking.o

fserver: forking_server.o networking.o
	gcc -o server forking_server.o networking.o

splayer: select_client.o networking.o
	gcc -o player select_client.o networking.o

player: player.o networking.o
	gcc -o player player.o networking.o

select_client.o: select_client.c networking.h
	gcc -c select_client.c

player.o: player.c networking.h
	gcc -c player.c

select_server.o: select_server.c networking.h
	gcc -c select_server.c

forking_server.o: forking_server.c networking.h
	gcc -c forking_server.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
