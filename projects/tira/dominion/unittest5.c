#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

//I followed the cardtest4.c example given to us, but many of my methods, formatting/comments, and variable name choices are my own.
int main() {
	//success and fail counts
	int numSuccess = 0;
	int numFail = 0;

	//initialize relevant card variables
	//most variables remain here for reusability, but unused variables are commented out
	//some of these values will change depending on the test and card effect choice
	int drawnCards = 0;
	int discarded = 1;
	//int deckDiscard = 0;
	//int netCoins = 0;
	int shuffledCards = 0;
	//int netActions = 0;
	int netSupply = -1;
	int gainedHand = 1;

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

	//*************************************************************************************************************
	// TEST 1: discard = copper, gain = silver
	printf("-- TEST 1: discard = copper, gain = silver --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on test
	choice1 = 0;
	choice2 = silver;
	postState.hand[currentPlayer][choice1] = copper;
	netSupply = -1;

	//call the card
	cardEffect(baron, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded + drawnCards + gainedHand);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - discarded + drawnCards + gainedHand)
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

	//copper supply should be unaffected
	printf("Test: copper supply = %d, expected = %d\tStatus: ", postState.supplyCount[copper], preState.supplyCount[copper] + 0);
	if (postState.supplyCount[copper] == preState.supplyCount[copper] + 0)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	//silver supply should decrease by 1
	printf("Test: silver supply = %d, expected = %d\tStatus: ", postState.supplyCount[silver], preState.supplyCount[silver] + netSupply);
	if (postState.supplyCount[silver] == preState.supplyCount[silver] + netSupply)
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

	//*************************************************************************************************************
	// TEST 2: discard = copper, gain = gold
	printf("-- TEST 2: discard = copper, gain = gold --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on test
	choice1 = 0;
	choice2 = gold;
	postState.hand[currentPlayer][choice1] = copper;
	//no expected change to gold supply
	netSupply = 0;

	//call the card
	int result;
	result = cardEffect(baron, choice1, choice2, choice3, &postState, handPos, &bonus);

	//copper supply should be unaffected
	printf("Test: copper supply = %d, expected = %d\tStatus: ", postState.supplyCount[copper], preState.supplyCount[copper] + 0);
	if (postState.supplyCount[copper] == preState.supplyCount[copper] + 0)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	//gold supply should be unaffected
	printf("Test: gold supply = %d, expected = %d\tStatus: ", postState.supplyCount[gold], preState.supplyCount[gold] + netSupply);
	if (postState.supplyCount[gold] == preState.supplyCount[gold] + netSupply)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	//should result in exit status of -1
	printf("Test: exit status = %d, expected = -1\tStatus: ", result);
	if (result == -1)
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

	printf("Tests completed for %s.\n", TESTCARD);
	printf("%d out of %d tests passed.\n\n", numSuccess, numSuccess + numFail);

	return 0;
}