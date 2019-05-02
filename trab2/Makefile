CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o market.o
	${CC} ${CFLAGS} -o ${OUT} bin/*.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c market-teste.c -o bin/market-teste.o

market.o: bin
	${CC} ${CFLAGS} -c market.c -o bin/market.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin