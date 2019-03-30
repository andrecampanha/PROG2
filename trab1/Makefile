CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o vetor.o jogos.o
	${CC} ${CFLAGS} -o ${OUT} bin/main.o bin/vetor.o bin/jogos.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c jogos-teste.c -o bin/main.o

jogos.o: bin
	${CC} ${CFLAGS} -c jogos.c -o bin/jogos.o

vetor.o: bin
	${CC} ${CFLAGS} -c vetor.c -o bin/vetor.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin