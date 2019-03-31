CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o vetor.o
	${CC} ${CFLAGS} -o ${OUT} bin/main.o bin/vetor.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c prob2.c -o bin/main.o

vetor.o: bin
	${CC} ${CFLAGS} -c vetor.c -o bin/vetor.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin