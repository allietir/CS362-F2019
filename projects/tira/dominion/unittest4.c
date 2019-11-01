#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "tribute"

//I followed the cardtest4.c example given to us, but many of my methods, formatting/comments, and variable name choices are my own.
int main() {
	//success and fail counts
	int numSuccess = 0;
	int numFail = 0;

	int i, j;
	int testCount = 0;
	char firstCard[10] = "";
	char secondCard[10] = "";

	//initialize relevant card variables
	//most variables remain here for reusability, but unused variables are commented out
	//some of these values will change depending on the test and card effect choice
	int drawnCards = 0;
	int discarded = 0;
	int deckDiscard = 0;
	int netCoins = 0;
	//int shuffledCards = 0;
	int netActions = 0;
	//int netSupply = 0;
	int gainedCards = 0;

	//initialize cardEffect() variables
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	//variables for initializeGame()
	int seed = 999;
	int numPlayers = 3;
	int currentPlayer = 0;
	int nextPlayer = currentPlayer + 1;

	//two game states used to compare card effects
	struct gameState preState, postState;

	//initialize card array
	int k[10] = {adventurer, minion, ambassador, gardens, mine, remodel, smithy, tribute, baron, great_hall};

	//initialize a game using pregame state
	initializeGame(numPlayers, k, seed, &preState);

	//set deck count of all other players equal to 10
	for ( i = 0; i < preState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			preState.deckCount[i] = 10;
		}
	}


	printf("----------------- Testing Card: %s -----------------\n\n", TESTCARD);

	//*************************************************************************************************************
	// TEST #: choice1 = 0 to preState.handCount[currentPlayer], choice2 = 0 to 3

	//call the card
	//int result = cardEffect(tribute, choice1, choice2, choice3, &postState, handPos, &bonus);

	//define arrays for top cards of deck, for now any action card will suffice
	int topCard[6] = {gold, gold, gold, estate, estate, baron};
	int nextTopCard[6] = {gold, estate, baron, estate, baron, baron};

	//test all 6 2-card combinations of revealed cards
	for (i = 0; i < 6; i++)
	{
		//copy pregame state over to post game
		memcpy(&postState, &preState, sizeof (struct gameState));

		postState.deck[nextPlayer][postState.deckCount[nextPlayer]-1] = topCard[i];
		postState.deck[nextPlayer][postState.deckCount[nextPlayer]-2] = nextTopCard[i];

		//reset card names
		strcpy(firstCard, "");
		strcpy(secondCard, "");

		//change variables based on revealed cards
		//if one of the cards is a treasure card
		if (topCard[i] == gold)
		{
			netCoins = 2;
			strcpy(firstCard, "treasure");
		}
		if (nextTopCard[i] == gold)
		{
			netCoins = 2;
			strcpy(secondCard, "treasure");
		}
		if (topCard[i] != gold && nextTopCard[i] != gold)
		{
			netCoins = 0;
		}
		//if one of the cards is a victory card
		if (topCard[i] == estate)
		{
			drawnCards = 2;
			strcpy(firstCard, "victory");
		}
		if (nextTopCard[i] == estate)
		{
			drawnCards = 2;
			strcpy(secondCard, "victory");
		}
		if (topCard[i] != estate && nextTopCard[i] != estate)
		{
			drawnCards = 0;
		}
		//if one of the cards is an action card
		if (topCard[i] == baron)
		{
			netActions = 2;
			strcpy(firstCard, "action");
		}
		if (nextTopCard[i] == baron)
		{
			netActions = 2;
			strcpy(secondCard, "action");
		}
		if (topCard[i] != baron && nextTopCard[i] != baron)
		{
			netActions = 0;
		}

		deckDiscard = 2;

		printf("-- TEST %d: deck count = 10, 1st card = %s, 2nd card = %s --\n", testCount + 1, firstCard, secondCard);

		cardEffect(tribute, choice1, choice2, choice3, &postState, handPos, &bonus);

		printf("Test: currentPlayer hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded + drawnCards);
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

		printf("Test: currentPlayer coins = %d, expected = %d\t\tStatus: ", postState.coins, preState.coins + netCoins);
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

		printf("Test: currentPlayer actions = %d, expected = %d\t\tStatus: ", postState.numActions, preState.numActions + netActions);
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

		printf("Test: nextPlayer deck count = %d, expected = %d\tStatus: ", postState.deckCount[nextPlayer], preState.deckCount[nextPlayer] - deckDiscard);
		if (postState.deckCount[nextPlayer] == preState.deckCount[nextPlayer] - deckDiscard)
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

		testCount++;
	}

	printf("Tests completed for %s.\n", TESTCARD);
	printf("%d out of %d tests passed.\n\n", numSuccess, numSuccess + numFail);

	return 0;
}