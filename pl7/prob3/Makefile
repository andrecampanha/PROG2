CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o avl.o
	${CC} ${CFLAGS} -o ${OUT} bin/main.o bin/avl.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c main.c -o bin/main.o

avl.o: bin
	${CC} ${CFLAGS} -c avl.c -o bin/avl.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin