CC=clang
CFLAGS=-g
RM=rm -f
OUT=prob
OUT2=tester

all: build

build: main.o market.o
	${CC} ${CFLAGS} -o ${OUT} bin/market-teste.o bin/market.o

build-2: trab2-tester.o market.o
	${CC} ${CFLAGS} -o ${OUT2} bin/trab2-tester.o bin/market.o

bin:
	if [ ! -d "bin" ]; then mkdir bin; fi

main.o: bin
	${CC} ${CFLAGS} -c market-teste.c -o bin/market-teste.o

trab2-tester.o: bin
	${CC} ${CFLAGS} -c trab2-tester.c -o bin/trab2-tester.o

market.o: bin
	${CC} ${CFLAGS} -c market.c -o bin/market.o

clean:
	rm -f bin/*.o ${OUT} ${OUT2}
	rmdir bin