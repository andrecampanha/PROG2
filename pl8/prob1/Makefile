CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o grafo.o vetor.o
	${CC} ${CFLAGS} -o ${OUT} bin/*.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c teste_grafo.c -o bin/main.o

grafo.o: bin
	${CC} ${CFLAGS} -c grafo.c -o bin/grafo.o

vetor.o: bin
	${CC} ${CFLAGS} -c vetor.c -o bin/vetor.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin