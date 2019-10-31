#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"

int main() {
	//success and fail counts
	int numSuccess = 0;
	int numFail = 0;

	//initialize relevant card variables
	int newCards = 0;
	int discarded = 0;
	int netCoins = 4;
	int shuffledCards = 0;
	int netBuys = 2;

	//int i, j;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 999;

	int numPlayers = 2;
	int currentPlayer = 0;

	struct gameState preState, postState;


	//initialize card array
	int k[10] = {adventurer, minion, ambassador, gardens, mine, remodel, smithy, tribute, baron, great_hall};


	//initialize a game
	initializeGame(numPlayers, k, seed, &preState);

	printf("---------- Testing Card: %s ----------\n", TESTCARD);

	// TEST 1: choice1 = 1 = discard estate, +4 gold
	printf("---- TEST 1: choice1 = 1 = discard estate, +4 gold ----\n");

	memcpy(&postState, &preState, sizeof (struct gameState));

	choice1 = 1;

	cardEffect(baron, choice1, choice2, choice3, &postState, handPos, &bonus);

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

	printf("Test: deck count = %d, expected = %d\tStatus: ", postState.deckCount[currentPlayer], preState.deckCount[currentPlayer] - newCards + shuffledCards);
	if (postState.deckCount[currentPlayer] == preState.deckCount[currentPlayer] - newCards + shuffledCards)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: coins = %d, expected = %d\tStatus: ", postState.coins[currentPlayer], preState.coins[currentPlayer] + netCoins);
	if (postState.coins[currentPlayer] == preState.coins[currentPlayer] + netCoins)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: buys = %d, expected = %d\tStatus: ", postState.numBuys[currentPlayer], preState.numBuys[currentPlayer] + netBuys);
	if (postState.numBuys[currentPlayer] == preState.numBuys[currentPlayer] + netBuys)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	// TEST 2: choice1 = 0 = do not discard estate, gain an estate
	printf("---- TEST 2: choice1 = 0 = do not discard estate, gain an estate ----\n");

	choice1 = 0;


	return 0;
}