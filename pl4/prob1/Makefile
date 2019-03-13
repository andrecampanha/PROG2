CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o lista.o
	${CC} ${CFLAGS} -o ${OUT} bin/main.o bin/lista.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c main.c -o bin/main.o

lista.o: bin
	${CC} ${CFLAGS} -c lista.c -o bin/lista.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin