CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o lista.o pilha.o
	${CC} ${CFLAGS} -o ${OUT} bin/main.o bin/lista.o bin/pilha.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c prob1.c -o bin/main.o

pilha.o: bin
	${CC} ${CFLAGS} -c pilha.c -o bin/pilha.o

lista.o: bin
	${CC} ${CFLAGS} -c lista.c -o bin/lista.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin