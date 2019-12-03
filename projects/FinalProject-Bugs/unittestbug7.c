/************************************************
* Author:		Kitch Kelly (kellykit)
* Date:			12/2/2019
* Description:	unittestbug7.c implements the unit
*				test for bug #7 of the CS 362 Final
*				Project.
************************************************/

#include "dominion.h"
#include <stdio.h> 
#include <stdlib.h>

# define player 0
# define leftPlayer 1

/*
Initialize the game by calling initializeGame().
Set the player’s hand to contain a tribute card.
Set the deck of the player to the left of the target player to contain two cards (the specific cards do not matter).
Call cardEffect on the target player’s tribute card.

NOTE: Had to re-insert old implementation of tribute function and comment out tributeRefactor()
*/


int main() {
	//Initialize the game
	struct gameState state;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, treasure_map, sea_hag };
	initializeGame(2, k, 13, &state);

	//Set player's hand to contain tribute card
	state.hand[player][0] = tribute;
	state.handCount[player] = 0;

	//Set the deck of the player to the left of the target player to contain two cards
	state.deck[leftPlayer][0] = adventurer;
	state.deck[leftPlayer][1] = adventurer;
	state.deckCount[leftPlayer] = 2;

	//set numActions to a known value
	state.numActions = 0;

	printf("\nTesting Bug #7: Tribute-card-loop-overrun\n");
	

	//Call cardEffect on the target player's tribute card.
	//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
	//only input that matters is card -> must be tribute
	cardEffect(tribute, 0, 0, 0, &state, 0, 0);

	//check result - two adventure cards should result in + 4 actions
	if (state.numActions == 4) {
		printf("Test Passed - Actual value of state.numActions matches expected result - should be 4\n");
	}
	else {
		printf("Error: Actual value of state.numActions does not match expected result\n");
		printf("\tExpected: %d; Actual: %d\n", 4, state.numActions);
	}

	return 0;
}