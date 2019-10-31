#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"

int main() {
	int newCards = 0;
	int discarded = 1;
	int extraCoins = 0;
	int shuffledCards = 0;

	int i, j, k;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

	//should be randomized
	int seed = 999;

	int numPlayers = 2;
	int thisPlayer = 0;

	struct gameState preState, postState;

	//initialize card array
	int k[10] = {adventurer, minion, ambassador, gardens, mine, remodel, smithy, tribute, baron, great_hall};


	//initialize a game
	initializeGame(numPlayers, k, seed, &preState);

	// TEST 1: choice1 = 1 = discard estate, +4 gold
	memcpy(&postState, &preState, sizeof (struct gameState));
	choice1 = 1;
	cardEffect(baron, choice1, choice2, choice3, &postState, handpo, &bonus);

	// TEST 2: choice1 = 0 = do not discard estate, gain an estate
	choice1 = 0;


	return 0;
}