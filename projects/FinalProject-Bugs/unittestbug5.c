/************************************************
* Author:		Kitch Kelly (kellykit)
* Date:			12/2/2019
* Description:	unittestbug5.c implements the unit
*				test for bug #5 of the CS 362 Final
*				Project.
************************************************/

#include "dominion.h"
#include <stdio.h> 
#include <stdlib.h>

# define player 0

/*
Initialize the game by calling initializeGame().
Set the player’s handCount and discardCount to 0.
Add one each of the cards that modify the player’s score
to the player's deck:
	- curse, estate, duchy, province, great hall, gardens
	- adding these cards should result in a score of 10
		- curse = -1
		- estate = +1
		- duchy = +3
		- province = +6
		- great hall = +1
		- gardens = all cards (in deck, discard, and hand) / 10
			- gardens = 0 b/c 6/10 rounds down to 0
Call the scoreFor() function on the player.
*/


int main() {
	//Initialize the game
	struct gameState state;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, treasure_map, sea_hag };
	initializeGame(2, k, 13, &state);

	//Set player's handCount and discardCount to 0
	state.handCount[player] = 0;
	state.discardCount[player] = 0;

	//Add one each of the cards that modify the player's score to the player's deck
	int deckCards[6] = { curse, estate, duchy, province, great_hall, gardens };

	int i;
	for (i = 0; i < 6; i++) {
		state.deck[player][i] = deckCards[i];
	}
	state.deckCount[player] = 6;

	//Call scoreFor() - should return 10 when the bug is fixed
	printf("\nTesting Bug #5: Incorrect-score-returned-from-scoreFor()\n");
	int score = scoreFor(player, &state);
	if (score == 10) {
		printf("Test Passed - Actual result matches expected result - should be 10\n");
	}
	else {
		printf("Error: Actual result does not match expected result\n");
		printf("\tExpected: %d; Actual: %d\n", 10, score);
	}

	return 0;
}