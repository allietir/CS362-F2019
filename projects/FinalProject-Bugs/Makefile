CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestbug1: unittestbug1.c dominion.o rngs.o
	gcc -o unittestbug1 -g unittestbug1.c dominion.o rngs.o $(CFLAGS)

unittestbug2: unittestbug2.c dominion.o rngs.o
	gcc -o unittestbug2 -g unittestbug2.c dominion.o rngs.o $(CFLAGS)

unittestbug3: unittestbug3.c dominion.o rngs.o
	gcc -o unittestbug3 -g unittestbug3.c dominion.o rngs.o $(CFLAGS)

unittestbug4: unittestbug4.c dominion.o rngs.o
	gcc -o unittestbug4 -g unittestbug4.c dominion.o rngs.o $(CFLAGS)

unittestbug5: unittestbug5.c dominion.o rngs.o
	gcc -o unittestbug5 -g unittestbug5.c dominion.o rngs.o $(CFLAGS)

unittestbug6: unittestbug6.c dominion.o rngs.o
	gcc -o unittestbug6 -g unittestbug6.c dominion.o rngs.o $(CFLAGS)

unittestbug7: unittestbug7.c dominion.o rngs.o
	gcc -o unittestbug7 -g unittestbug7.c dominion.o rngs.o $(CFLAGS)

unittestbug8: unittestbug8.c dominion.o rngs.o
	gcc -o unittestbug8 -g unittestbug8.c dominion.o rngs.o $(CFLAGS)

unittestbug9: unittestbug9.c dominion.o rngs.o
	gcc -o unittestbug9 -g unittestbug9.c dominion.o rngs.o $(CFLAGS)

unittestbug10: unittestbug10.c dominion.o rngs.o
	gcc -o unittestbug10 -g unittestbug10.c dominion.o rngs.o $(CFLAGS)

unittestresults: unittestbug1 unittestbug2 unittestbug3 unittestbug4 unittestbug5 unittestbug6 unittestbug7 unittestbug8 unittestbug9 unittestbug10
	./unittestbug1 &> unittestresults.out
	./unittestbug2 &>> unittestresults.out
	./unittestbug3 &>> unittestresults.out
	./unittestbug4 &>> unittestresults.out
	./unittestbug5 &>> unittestresults.out
	./unittestbug6 &>> unittestresults.out
	./unittestbug7 &>> unittestresults.out
	./unittestbug8 &>> unittestresults.out
	./unittestbug9 &>> unittestresults.out
	./unittestbug10 &>> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out
