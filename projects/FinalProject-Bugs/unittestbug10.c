/***********************************************************
 *
 *	Richard Logan Seals
 *	OSU CS362 - Fall2019
 *	
 *
 * 	Name: unitestbug10.c
 *	Description: This file is a test file for the ambassador card
 *	in the dominion.c game.
 * *******************************************************/

#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

/**************************************************************************
 * This is my own assert function that will test the value of two integers and print
 * an error message if the two integer arguments are not equal to each other.
 * The function takes an integer for the expected value, an integer for the actual
 * value, and a pointer to a character that is the message to print to the console.
 * THe function does not return anything.
 ************************************************************************/
void myAssert(int expected, int actual, char* message){

	if(expected == actual)
		return;

	else{

		printf("ERROR: %s\n", message);

	}
};


int main(){

	// print to screen the function to be tested
	printf("\n**************Testing ambassador card*******************\n");


	printf("\nusing ambassador to discard a curse card\n");
	// define variables to set up a gamestate
	int c[10]={adventurer, council_room, feast, gardens, baron, remodel, smithy, village, great_hall, mine};
	struct gameState* g = newGame();

	// set up a game to start the test
	initializeGame(3, c,65, g);


	// set handcount to 1
	g->handCount[0] = 4;

	// empty player1's hand of cards
	for(int j = 0; j < 5; j++){

		g->hand[0][j] = -1;
	}

	// add baron and estate to player's hand
	g->hand[0][0] = ambassador;
	g->hand[0][1] = curse;
	g->hand[0][2] = curse;
	g->hand[0][3] = curse;

	int bonus = 0;

	int result = cardEffect(g->hand[0][0], 1, 1, 0, g, 0, &bonus);

	char mes[] = "cardEffect() returned -1 for valid call\n";
	myAssert(result, 0, mes);

	char mes1[] = "correct number of curses were not removed from player's hand";

	if(result == 0){

		int numCurses = 0;
		for(int x = 0; x < g->handCount[0]; x++){

			if(g->hand[0][x] == curse)
				numCurses++;
		}

		myAssert(numCurses, 2, mes1);

		if(numCurses != 2)
			printf("number of curses in hand: %d; expected 2\n", numCurses);
	}



	printf("\nusing ambassador to discard two curse cards\n");

	// set up a game to start the test
	initializeGame(3, c,65, g);

	// set handcount to 1
	g->handCount[0] = 4;

	// empty player1's hand of cards
	for(int j = 0; j < 5; j++){

		g->hand[0][j] = -1;
	}

	// add baron and estate to player's hand
	g->hand[0][0] = ambassador;
	g->hand[0][1] = curse;
	g->hand[0][2] = curse;
	g->hand[0][3] = curse;

	bonus = 0;

	result = cardEffect(g->hand[0][0], 1, 2, 0, g, 0, &bonus);

	myAssert(result, 0, mes);


	if(result == 0){

		int numCurses = 0;
		for(int x = 0; x < g->handCount[0]; x++){

			if(g->hand[0][x] == curse)
				numCurses++;
		}

		myAssert(numCurses, 1, mes1);

		if(numCurses != 1)
			printf("number of curses in hand: %d; expected 1\n", numCurses);
	}



	printf("\nusing ambassador to discard no curse cards\n");

	// set up a game to start the test
	initializeGame(3, c,65, g);

	// set handcount to 1
	g->handCount[0] = 4;

	// empty player1's hand of cards
	for(int j = 0; j < 5; j++){

		g->hand[0][j] = -1;
	}

	// add baron and estate to player's hand
	g->hand[0][0] = ambassador;
	g->hand[0][1] = curse;
	g->hand[0][2] = curse;
	g->hand[0][3] = curse;

	bonus = 0;

	result = cardEffect(g->hand[0][0], 1, 0, 0, g, 0, &bonus);

	myAssert(result, 0, mes);

	if(result == 0){

		int numCurses = 0;
		for(int x = 0; x < g->handCount[0]; x++){

			if(g->hand[0][x] == curse)
				numCurses++;
		}

		myAssert(numCurses, 3, mes1);

		if(numCurses != 3)
			printf("number of curses in hand: %d; expected 3\n", numCurses);
	}


	return 0;
}
