CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o pilha.o
	${CC} ${CFLAGS} -o ${OUT} bin/main.o bin/pilha.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c main.c -o bin/main.o

pilha.o: bin
	${CC} ${CFLAGS} -c pilha.c -o bin/pilha.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin