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

	int i;

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
	int numPlayers = 3;
	int currentPlayer = 0;

	//two game states used to compare card effects
	struct gameState preState, postState;

	//initialize card array
	int k[10] = {adventurer, minion, ambassador, gardens, mine, remodel, smithy, tribute, baron, great_hall};

	//initialize a game using pregame state
	initializeGame(numPlayers, k, seed, &preState);

	printf("----------------- Testing Card: %s -----------------\n\n", TESTCARD);

	//*************************************************************************************************************
	// TEST 1: choice1 = 1 = discard estate, +4 gold
	printf("-- TEST 1: choice1 = 1 = +2 gold --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on card effects
	choice1 = 1;
	netCoins = 2;

	//call the card
	cardEffect(minion, choice1, choice2, choice3, &postState, handPos, &bonus);

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

	printf("Test: coins = %d, expected = %d\t\tStatus: ", postState.coins, preState.coins + netCoins);
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

	printf("Test: actions = %d, expected = %d\t\tStatus: ", postState.numActions, preState.numBuys + netActions);
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

	for ( i = 0; i < postState.numPlayers; i++)
	{
		printf("Test: player %d hand count = %d, expected = %d\tStatus: ", i + 1, postState.handCount[i], preState.handCount[i] - discarded + drawnCards);
		if (postState.handCount[i] == preState.handCount[i] - discarded + drawnCards)
		{
			printf("SUCCESS\n");
			numSuccess++;
		}
		else
		{
			printf("FAIL\n");
			numFail++;
		}
	}

	printf("\n");

	//*************************************************************************************************************
	// TEST 2: choice2 = 1, discard hand, redraw 4, no other player has 5 cards
	printf("-- TEST 2: choice2 = 1, discard hand, redraw 4, no other player has 5 cards --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on card effects
	choice1 = 0;
	choice2 = 1;
	netCoins = 0;
	discarded = preState.handCount[currentPlayer];
	drawnCards = 4;

	//change other player's hands to a number that is not 5
	for ( i = 0; i < postState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			postState.handCount[i] = 4;
		}
	}

	//call the card
	cardEffect(minion, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: player %d hand count = %d, expected = %d\tStatus: ", currentPlayer + 1, postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded + drawnCards);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - discarded + drawnCards)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: player %d deck count = %d, expected = %d\tStatus: ", currentPlayer + 1, postState.deckCount[currentPlayer], preState.deckCount[currentPlayer] - drawnCards + shuffledCards);
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

	printf("Test: player %d coins = %d, expected = %d\t\tStatus: ", currentPlayer + 1, postState.coins, preState.coins + netCoins);
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

	printf("Test: player %d actions = %d, expected = %d\t\tStatus: ", currentPlayer + 1, postState.numActions, preState.numBuys + netActions);
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

	//tests for players who are not the current player
	for ( i = 0; i < postState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			discarded = 0;
			drawnCards = 0;
			shuffledCards = 0;

			printf("Test: player %d hand count = %d, expected = %d\tStatus: ", i + 1, postState.handCount[i], preState.handCount[i] - discarded + drawnCards);
			if (postState.handCount[i] == preState.handCount[i] - discarded + drawnCards)
			{
				printf("SUCCESS\n");
				numSuccess++;
			}
			else
			{
				printf("FAIL\n");
				numFail++;
			}

			printf("Test: player %d deck count = %d, expected = %d\tStatus: ", i + 1, postState.deckCount[i], preState.deckCount[i] - drawnCards + shuffledCards);
			if (postState.deckCount[i] == preState.deckCount[i] - drawnCards + shuffledCards)
			{
				printf("SUCCESS\n");
				numSuccess++;
			}
			else
			{
				printf("FAIL\n");
				numFail++;
			}
		}
	}

	printf("\n");

	//*************************************************************************************************************
	// TEST 3: choice2 = 1, discard hand, redraw 4, all other player has 5 cards
	printf("-- TEST 3: choice2 = 1, discard hand, redraw 4, all other player has 5 cards --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on card effects
	choice1 = 0;
	choice2 = 1;
	netCoins = 0;

	//change other player's hand counts to 5
	for ( i = 0; i < postState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			postState.handCount[i] = 5;
		}
	}

	//call the card
	cardEffect(minion, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: player %d hand count = %d, expected = %d\tStatus: ", currentPlayer + 1, postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded + drawnCards);
	if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - discarded + drawnCards)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: player %d deck count = %d, expected = %d\tStatus: ", currentPlayer + 1, postState.deckCount[currentPlayer], preState.deckCount[currentPlayer] - drawnCards + shuffledCards);
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

	printf("Test: player %d coins = %d, expected = %d\t\tStatus: ", currentPlayer + 1, postState.coins, preState.coins + netCoins);
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

	printf("Test: player %d actions = %d, expected = %d\t\tStatus: ", currentPlayer + 1, postState.numActions, preState.numBuys + netActions);
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

	//tests for players who are not the current player
	for ( i = 0; i < postState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			discarded = preState.handCount[i];
			drawnCards = 4;
			shuffledCards = 0;

			printf("Test: player %d hand count = %d, expected = %d\tStatus: ", i + 1, postState.handCount[i], preState.handCount[i] - discarded + drawnCards);
			if (postState.handCount[i] == preState.handCount[i] - discarded + drawnCards)
			{
				printf("SUCCESS\n");
				numSuccess++;
			}
			else
			{
				printf("FAIL\n");
				numFail++;
			}

			printf("Test: layer %d deck count = %d, expected = %d\tStatus: ", i + 1, postState.deckCount[i], preState.deckCount[i] - drawnCards + shuffledCards);
			if (postState.deckCount[i] == preState.deckCount[i] - drawnCards + shuffledCards)
			{
				printf("SUCCESS\n");
				numSuccess++;
			}
			else
			{
				printf("FAIL\n");
				numFail++;
			}
		}
	}

	printf("\n");

	printf("Tests completed for %s.\n", TESTCARD);
	printf("%d out of %d tests passed.\n\n", numSuccess, numSuccess + numFail);

	return 0;
}