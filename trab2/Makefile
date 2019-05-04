CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob

all: build

build: main.o market.o
	${CC} ${CFLAGS} -o ${OUT} bin/market-teste.o bin/market.o

build-2: teste2.o market.o
	${CC} ${CFLAGS} -o ./test2 bin/market-teste2.o bin/market.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c market-teste.c -o bin/market-teste.o

teste2.o: bin
	${CC} ${CFLAGS} -c market-teste2.c -o bin/market-teste2.o

market.o: bin
	${CC} ${CFLAGS} -c market.c -o bin/market.o

clean:
	rm -f bin/*.o ${OUT}
	rmdir bin