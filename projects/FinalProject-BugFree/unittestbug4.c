/************************************************
* Author:		Kitch Kelly (kellykit)
* Date:			12/2/2019
* Description:	unittestbug4.c implements the unit
*				test for bug #4 of the CS 362 Final
*				Project.
************************************************/

#include "dominion.h"
#include <stdio.h> 
#include <stdlib.h>

/*
Initialize the game with the required kingdom cards. 
The required cards are those greater than or equal to 25 according to the enumeration described in dominion.c 
(being Treasure Map and Sea Hag - the other kingdom cards can be chosen at random).

Set the supply count of the required kingdom cards to 0 and call the isGameOver() function. 
This function call should return 0 because the card count of only two supply piles are equal to 0.

Set the supply count of one more card to 0 (the exact card can be chosen at random) and call the isGameOver() function again. 
This function call should return 1 because the card count of three supply piles are equal to 0, 
which represents that the isGameOver() function recognizes that the end-game state has been reached.
*/



int main() {
	//initialize game with required cards (treasure_map and sea_hag)
	struct gameState state;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, treasure_map, sea_hag };
	initializeGame(2, k, 13, &state);

	//set supplyCounts of required cards to 0
	state.supplyCount[treasure_map] = 0;
	state.supplyCount[sea_hag] = 0;

	//Test isGameOver - should return 0, representing that end-game state has not been reached
	printf("\nTesting Bug #4: isGameOver()-card-iteration-error\n");
	printf("\nTest 1: Supply of last two cards in CARD enum set to 0\n");

	int result = isGameOver(&state);
	if (result == 0) {
		printf("Test Passed - Actual result matches expected result - should be 0\n");
	}
	else {
		printf("Error: Actual result does not match expected result\n");
		printf("\tExpected: %d; Actual: %d\n", 0, result);
	}

	//set supplyCount of one non-required card to 0
	state.supplyCount[adventurer] = 0;

	//Test isGameOver - should return 1, indicating that end-game state has been reached
	printf("\nTest 2: Supply of last two cards in CARD enum + one more card set to 0\n");
	result = isGameOver(&state);

	if (result == 1) {
		printf("Test Passed - Actual result matches expected result - should be 1\n");
	}
	else {
		printf("Error: Actual result does not match expected result\n");
		printf("\tExpected: %d; Actual: %d\n", 1, result);
	}
	return 0;
}