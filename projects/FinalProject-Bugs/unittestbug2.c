#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

int main() {
	//success and fail counts
	int numSuccess = 0;
	int numFail = 0;

	//initialize relevant card variables
	int drawnCards = 0;
	int trashed = 1;
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

	printf("----------------- Testing for Bug #2 in Card: %s -----------------\n\n", TESTCARD);

	//*************************************************************************************************************
	// TEST 1: discard = copper, gain = silver
	printf("-- TEST 1: trash = copper, gain = silver --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on test
	choice1 = 0;
	choice2 = silver;
	postState.hand[currentPlayer][choice1] = copper;

	//call the card
	int result = cardEffect(mine, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}


	printf("Test: exit status = %d, expected = 0\tStatus: ", result);
	if (result == 0)
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
	// TEST 2: discard = copper, gain = silver
	printf("-- TEST 2: trash = silver, gain = gold --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on test
	choice1 = 0;
	choice2 = gold;
	postState.hand[currentPlayer][choice1] = silver;

	//call the card
	cardEffect(mine, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}


	printf("Test: exit status = %d, expected = 0\tStatus: ", result);
	if (result == 0)
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
	// TEST 3: discard = copper, gain = copper
	printf("-- TEST 3: trash = copper, gain = copper --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on test
	choice1 = 0;
	choice2 = copper;
	postState.hand[currentPlayer][choice1] = copper;

	//call the card
	cardEffect(mine, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}


	printf("Test: exit status = %d, expected = 0\tStatus: ", result);
	if (result == 0)
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
	// TEST 4: discard = silver, gain = copper
	printf("-- TEST 4: trash = silver, gain = copper --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on test
	choice1 = 0;
	choice2 = copper;
	postState.hand[currentPlayer][choice1] = silver;

	//call the card
	cardEffect(mine, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}


	printf("Test: exit status = %d, expected = 0\tStatus: ", result);
	if (result == 0)
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
	// TEST 5: discard = silver, gain = copper
	printf("-- TEST 5: trash = gold, gain = copper --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on test
	choice1 = 0;
	choice2 = copper;
	postState.hand[currentPlayer][choice1] = gold;

	//call the card
	cardEffect(mine, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - trashed + drawnCards + gainedHand - 1)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}


	printf("Test: exit status = %d, expected = 0\tStatus: ", result);
	if (result == 0)
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