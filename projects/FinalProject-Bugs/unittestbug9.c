/***********************************************************
 *
 *	Richard Logan Seals
 *	OSU CS362 - Fall2019
 *	
 *
 * 	Name: unitestbug9.c
 *	Description: This file is a test file for the tribute card
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
	printf("\n**************Testing tribute duplicate revealed cards*******************\n");

	// define variables to set up a gamestate
	int c[10]={adventurer, council_room, feast, gardens, baron, remodel, smithy, village, great_hall, mine};
	struct gameState* g = newGame();

	// set up a game to start the test
	initializeGame(3, c,65, g);

	g->coins = 0;
	g->numActions = 1;

	int numCoins = g->coins;
	int numActions = g->numActions;

	// set handcount to 1
	g->handCount[0] = 1;

	g->discardCount[1] = 0;
	g->deckCount[1] = 10;

	for(int x = 0; x < 10; x++){
		g->deck[1][x] = gold;
	}


	// empty player1's hand of cards
	for(int j = 0; j < 5; j++){

		g->hand[0][j] = -1;
	}

	// add baron and estate to player's hand
	g->hand[0][0] = tribute;

	int bonus = 0;

	cardEffect(g->hand[0][0], 0, 0, 0, g, g->hand[0][0], &bonus);

	// tributeEffect(g, 0);

	char mes[] = "number of coins not increased by 2";	
	myAssert(numCoins + 2, g->coins, mes);

	char mes1[] = "number of actions increased";
	myAssert(g->numActions, numActions, mes1);

	if(g->coins == 2 && g->numActions == 1){
		printf("Unit test passed!\n\n");
	}
	else{
		printf("number of coins: %d\n", g->coins);
		printf("number of actions: %d\n\n", g->numActions);
	}

	return 0;
}

