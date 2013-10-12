# Makefile ( C++11 needed )

CC = g++
CFLAGS = -std=c++11 -s
LDFLAGS = -l pthread

Tetris_Game: Tetris_Game.o
	${CC} ${CFLAGS} ${LDFLAGS} -o Tetris_Game Tetris_Game.o
	rm -f Tetris_Game.o 

Tetris_Game.o: Tetris_Game.cpp
	${CC} ${CFLAGS} -c Tetris_Game.cpp 

clean:
	rm -f Tetris_Game Tetris_Game.o 
