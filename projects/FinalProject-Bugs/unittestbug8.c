/***********************************************************
 *
 *	Richard Logan Seals
 *	OSU CS362 - Fall2019
 *	
 *
 * 	Name: unitestbug8.c
 *	Description: This file is a test file for the coin bonuses
 *	in the dominion.c game.
 * *******************************************************/

#include <stdio.h>
#include <string.h>
#include "dominion.h"

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
	printf("\n**************Testing bonus coins*******************\n");

	printf("\nTesting with Steward card\n");

	// define variables to set up a gamestate
	int c[10]={adventurer, council_room, feast, gardens, baron, remodel, smithy, village, great_hall, mine};
	struct gameState* g = newGame();

	// set up a game to start the test
	initializeGame(2, c, 5, g);

	// set handcount to 1
	g->handCount[0] = 1;

	// set coins to 0
	g->coins = 0;

	// empty player1's hand of cards
	for(int j = 0; j < 5; j++){

		g->hand[0][j] = -1;
	}

	// add baron and estate to player's hand
	g->hand[0][0] = steward;

	playCard(0, 2, 0, 0, g);

	char mes[] = "number of coins not increased by 2";	
	myAssert(g->coins, 2, mes);

	if(g->coins == 2){
		printf("Unit test passed!\n");
	}
	else{
		printf("number of coins: %d\n\n", g->coins);
	}

	printf("\nTesting with Minion card and gold in hand\n");

	initializeGame(4, c, 88, g);
	
	// set handcount to 2
	g->handCount[0] = 2;


	g->coins = 0;

	// empty player1's hand of cards
	for(int j = 0; j < 5; j++){

		g->hand[0][j] = -1;
	}

	// add baron and estate to player's hand
	g->hand[0][0] = minion;
	g->hand[0][1] = gold;

	playCard(0, 2, 0, 0, g);

	myAssert(g->coins, 5, mes);

	if(g->coins == 5){
		printf("Unit test passed!\n");
	}
	else{
		printf("number of coins: %d\n\n", g->coins);
	}



	return 0;
}
