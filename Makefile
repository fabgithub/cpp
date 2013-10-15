# Makefile ( C++11 needed )

CC = g++
PG = Tetris_Game
SOURCE = Tetris_Game.cpp
OBJECTS = Tetris_Game.o
CFLAGS = -std=c++11 -s -Wall -O3
LDLIBS = -l pthread

${PG}: ${OBJECTS}
	${CC} ${CFLAGS} ${LDLIBS} -o ${PG} ${OBJECTS}
	rm -f ${OBJECTS}

${OBJECTS}: ${SOURCE}
	${CC} ${CFLAGS} -c ${SOURCE}

clean:
	rm -f ${PG} ${OBJECTS}
