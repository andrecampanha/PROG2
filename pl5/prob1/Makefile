CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o armazem.o contentor.o pilha_contentores.o fila_contentores.o
	${CC} ${CFLAGS} -o ${OUT} bin/main.o bin/armazem.o bin/contentor.o bin/pilha_contentores.o bin/fila_contentores.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c teste_armazem.c -o bin/main.o

armazem.o: bin
	${CC} ${CFLAGS} -c armazem.c -o bin/armazem.o

contentor.o: bin
	${CC} ${CFLAGS} -c contentor.c -o bin/contentor.o

pilha_contentores.o: bin
	${CC} ${CFLAGS} -c pilha_contentores.c -o bin/pilha_contentores.o

fila_contentores.o: bin
	${CC} ${CFLAGS} -c fila_contentores.c -o bin/fila_contentores.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin