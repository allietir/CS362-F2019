/************************************************
* Author:		Kitch Kelly (kellykit)
* Date:			12/2/2019
* Description:	unittestbug6.c implements the unit
*				test for bug #6 of the CS 362 Final
*				Project.
************************************************/

#include "dominion.h"
#include <stdio.h> 
#include <stdlib.h>

# define player 0

/*
Initialize the game by calling initializeGame().
Set the player’s hand to contain one feast card.
Call cardEffect on the player’s feast card.
Choose to buy a card costing less than 5 coins
	- smithy used in this case (cost = 4 coins)
*/


int main() {
	//Initialize the game
	struct gameState state;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, treasure_map, sea_hag };
	initializeGame(2, k, 13, &state);
	state.coins = 0;

	//Set player's hand to contain one feast card
	state.hand[player][0] = feast;
	state.handCount[player] = 1;

	//Call cardEffect on player's feast card
	//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
	//card = feast; choice1 = card to gain (smithy in this case); no other input matters
	cardEffect(feast, smithy, 0, 0, &state, 0, 0);

	printf("\nTesting Bug #6: feast-logic-error\n");
	if (state.coins == 0) {
		printf("Test Passed - Actual value of state.coins matches expected result - should be 0\n");
	}
	else {
		printf("Error: Actual value of state.coins does not match expected result\n");
		printf("\tExpected: %d; Actual: %d\n", 0, state.coins);
	}
	return 0;
}