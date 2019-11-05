CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

randomtestresults: 	
	./testme &> randomtestresults.out
	gcov testme.c -b -f >> randomtestresults.out
	cat testme.c.gcov >> randomtestresults.out

all: testme randomtestresults

clean:
	rm -f testme *.o *.gcov *gcno *.out *.gcda