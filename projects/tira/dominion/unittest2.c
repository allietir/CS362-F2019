#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"

//I followed the cardtest4.c example given to us, but many of my methods, formatting/comments, and variable name choices are my own.
int main() {
	//success and fail counts
	int numSuccess = 0;
	int numFail = 0;

	//int i;

	//initialize relevant card variables
	//most variables remain here for reusability, but unused variables are commented out
	//some of these values will change depending on the test and card effect choice
	int drawnCards = 0;
	int discarded = 0;
	int netCoins = 0;
	int shuffledCards = 0;
	int netActions = 1;
	//int netSupply = 0;

	//initialize cardEffect() variables
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	//variables for initializeGame()
	int seed = 999;
	int numPlayers = 2;
	int currentPlayer = 0;

	//two game states used to compare card effects
	struct gameState preState, postState;

	//initialize card array
	int k[10] = {adventurer, minion, ambassador, gardens, mine, remodel, smithy, tribute, baron, great_hall};

	//initialize a game using pregame state
	initializeGame(numPlayers, k, seed, &preState);

	printf("----------------- Testing Card: %s -----------------\n\n", TESTCARD);


	// TEST 1: choice1 = 1 = discard estate, +4 gold
	printf("-- TEST 1: choice1 = 1 = +2 gold --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on card effects
	choice1 = 1;
	netCoins = 2;

	//call the card
	cardEffect(minion, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - discarded)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: deck count = %d, expected = %d\tStatus: ", postState.deckCount[currentPlayer], preState.deckCount[currentPlayer] - drawnCards + shuffledCards);
	if (postState.deckCount[currentPlayer] == preState.deckCount[currentPlayer] - drawnCards + shuffledCards)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: coins = %d, expected = %d\tStatus: ", postState.coins, preState.coins + netCoins);
	if (postState.coins == preState.coins + netCoins)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: actions = %d, expected = %d\tStatus: ", postState.numActions, preState.numBuys + netActions);
	if (postState.numActions == preState.numActions + netActions)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("\n");

	// TEST 2: choice1 = 1, no estate card in hand

	printf("Tests completed for %s.\n", TESTCARD);
	printf("%d out of %d tests passed.\n\n", numSuccess, numSuccess + numFail);

	return 0;
}