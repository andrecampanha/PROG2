CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o avl.o bst.o
	${CC} ${CFLAGS} -o ${OUT} bin/main.o bin/avl.o bin/bst.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c main.c -o bin/main.o

avl.o: bin
	${CC} ${CFLAGS} -c avl.c -o bin/avl.o

bst.o: bin
	${CC} ${CFLAGS} -c bst.c -o bin/bst.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin