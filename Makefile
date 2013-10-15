# Makefile ( C++11 needed )

CC = g++
PG = Tetris_Game
SOURCE = Tetris_Game.cpp
OBJECTS = Tetris_Game.o
CFLAGS = -std=c++11 -s
LDFLAGS = -l pthread

${PG}: ${OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} -o ${PG} ${OBJECTS}
	rm -f ${OBJECTS}

${OBJECTS}: ${SOURCE}
	${CC} ${CFLAGS} -c ${SOURCE}

clean:
	rm -f ${PG} ${OBJECTS}
