CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

runtest: testme
	./testme

all: testme runtest

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out
