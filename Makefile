ai.o: ai.c analysis.o board.o pieces.o player.o util.o
	gcc -c ai.c -o ai.o

analysis.o: analysis.c board.o pieces.o player.o util.o
	gcc -c analysis.c -o analysis.o

board.o: board.c player.o util.o
	gcc -c board.c -o board.o

pieces.o: pieces.c board.o player.o util.o
	gcc -c pieces.c -o pieces.o

player.o: player.c
	gcc -c player.c -o player.o

util.o: util.c
	gcc -c util.c -o util.o

linux_io.o: linux_io.c ai.o analysis.o board.o pieces.o player.o util.o
	gcc -c linux_io.c -o linux_io.o

linux_io: linux_io.o ai.o analysis.o board.o pieces.o player.o util.o
	gcc -o linux_io linux_io.o ai.o analysis.o board.o pieces.o player.o util.o