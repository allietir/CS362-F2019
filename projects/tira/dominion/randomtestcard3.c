#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "tribute"
#define NUMTESTS 1000

int main() {
	//seed rand
	srand(time(NULL));

	//success and test counts
	int numSuccess = 0;
	int testCount = 0;

	int i, j;

	//initialize relevant card variables
	//most variables remain here for reusability, but unused variables are commented out
	//some of these values will change depending on the test and card effect choice
	int drawnCards = 0;
	int discarded = 0;
	int netCoins = 0;
	int shuffledCards = 0;
	int netBuys = 1;
	int netSupply = 0;

	//initialize cardEffect() variables
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	//variables for initializeGame()
	int seed;
	int numPlayers;
	int currentPlayer;

	//decides if an estate will be placed
	int placeEstate;

	//two game states used to compare card effects
	struct gameState preState, postState;

	//initialize card array
	//i am deciding to keep the card array consistent for each test
	int k[10] = {adventurer, minion, ambassador, gardens, mine, remodel, smithy, tribute, baron, great_hall};

	printf("----------------- Testing Card: %s -----------------\n\n", TESTCARD);

	//Randomize the gamestate
	for (i = 0; i < NUMTESTS; i++)
	{
		//randomize 1-4 players
		numPlayers = (rand() % 4) + 1;
		//randomize seed
		seed = rand() % 999999999;
		//randomize current player
		currentPlayer = rand() % numPlayers;

		//initialize a game using pregame state
		initializeGame(numPlayers, k, seed, &preState);

		//randomize deck size of current player
		preState.deckCount[currentPlayer] = rand() % 30;

		//randomize hand count, 1-5, so that there will always be at least 1 card in hand
		//since playing baron is not possible if it was not in your hand
		preState.handCount[currentPlayer] = (rand() % 5) + 1;

		//randomize position of estate card in hand
		//also add a chance of no estate card in hand
		placeEstate = rand() % (preState.handCount[currentPlayer] + 1);
		if (placeEstate < preState.handCount[currentPlayer])
		{
			//place the estate
			preState.hand[currentPlayer][placeEstate] = estate;
			estateInHand = 1;
		}
		else //no estates
		{
			//get rid of any estates in hand
			for ( j = 0; j < preState.handCount[currentPlayer]; j++)
			{
				if (preState.hand[currentPlayer][j] == estate)
				{
					preState.hand[currentPlayer][j] = mine;
				}
				estateInHand = 0;
			}
		}

		//randomize player choice
		choice1 = rand() % 2;
		if (choice1 == 0)
		{
			//change choice variables based on card effects
			discarded = 0;
			netCoins = 0;
			netSupply = -1;
		}
		else if (choice1 == 1)
		{
			//change choice variables based on card effects
			discarded = 1;
			netCoins = 4;
			netSupply = 0;
		}

		//copy pregame state over to post game
		memcpy(&postState, &preState, sizeof (struct gameState));

		//call the card
		cardEffect(baron, choice1, choice2, choice3, &postState, handPos, &bonus);

		//test handcount
		testCount++;
		if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - discarded + drawnCards)
		{
			numSuccess++;
		}
		else
		{
			printf("TEST #%d FAILED: incorrect handcount\n", testCount);
		}

		//test deckcount
		testCount++;
		if (postState.deckCount[currentPlayer] == preState.deckCount[currentPlayer] - drawnCards + shuffledCards)
		{
			numSuccess++;
		}
		else
		{
			printf("TEST #%d FAILED: incorrect deckcount\n", testCount);
		}

		//test coins
		testCount++;
		if (postState.coins == preState.coins + netCoins)
		{
			numSuccess++;
		}
		else
		{
			printf("TEST #%d FAILED: incorrect coins\n", testCount);
		}

		//test buys
		testCount++;
		if (postState.numBuys == preState.numBuys + netBuys)
		{
			numSuccess++;
		}
		else
		{
			printf("TEST #%d FAILED: incorrect buys\n", testCount);
		}

		//test estate supply
		testCount++;
		if (postState.supplyCount[estate] == preState.supplyCount[estate] + netSupply)
		{
			numSuccess++;
		}
		else
		{
			printf("TEST #%d FAILED: incorrect estate supply\n", testCount);
		}
	}

	printf("\n");

	printf("Tests completed for %s.\n", TESTCARD);
	printf("%d out of %d tests passed.\n\n", numSuccess, testCount);

	return 0;
}

int main() {
	//success and fail counts
	int numSuccess = 0;
	int numFail = 0;

	int i;
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
	//int gainedCards = 0;

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

	printf("----------------- Testing Card: %s -----------------\n\n", TESTCARD);

	//define arrays for top cards of deck, for now any action card will suffice
	int topCard[6] = {gold, gold, gold, estate, estate, baron};
	int nextTopCard[6] = {gold, estate, baron, estate, baron, baron};

	//*************************************************************************************************************************************
	//set deck count of all other players equal to 10
	for ( i = 0; i < preState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			preState.deckCount[i] = 10;
		}
	}

	//test all 6 2-card combinations of revealed cards at deck count of 10
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

		//enough cards to discard top 2 cards of deck
		deckDiscard = 2;

		printf("-- TEST %d: nextPlayer deck count = 10, 1st card = %s, 2nd card = %s --\n", testCount + 1, firstCard, secondCard);

		//call the tribute card
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

		printf("Test: nextPlayer deck count = %d, expected = %d\t\tStatus: ", postState.deckCount[nextPlayer], preState.deckCount[nextPlayer] - deckDiscard);
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

	//*************************************************************************************************************************************
	//set deck count of all other players equal to 1 and discard count to 5 to trigger a "shuffle"
	for ( i = 0; i < preState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			preState.deckCount[i] = 1;
			preState.discardCount[i] = 5;
		}
	}

	//test all combinations
	for (i = 0; i < 6; i++)
	{
		//copy pregame state over to post game
		memcpy(&postState, &preState, sizeof (struct gameState));

		postState.deck[nextPlayer][postState.deckCount[nextPlayer]-1] = topCard[i];

		//By disabling the call to shuffle() in tributeRefactor, we can test with expected knowledge of the top card after
		//the discard is "shuffled" back into the deck.
		postState.discard[nextPlayer][preState.discardCount[nextPlayer]-1] = nextTopCard[i];

		//reset card names
		strcpy(firstCard, "");
		strcpy(secondCard, "");

		//change variables based on revealed cards
		//if top card is a treasure card
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

		//still discarding 2 cards total, only after post shuffle
		deckDiscard = 2;

		printf("-- TEST %d: nextPlayer deck count = 1, 1st card = %s, 2nd card = %s --\n", testCount + 1, firstCard, secondCard);

		//call the tribute card
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

		printf("Test: nextPlayer deck count = %d, expected = %d\t\tStatus: ", postState.deckCount[nextPlayer], preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard);
		if (postState.deckCount[nextPlayer] == preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard)
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

	//*************************************************************************************************************************************
	//set deck count of all other players equal to 0 and discard count to 5 to trigger a shuffle
	for ( i = 0; i < preState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			preState.deckCount[i] = 0;
			preState.discardCount[i] = 5;
		}
	}

	//test all card combinations
	for (i = 0; i < 6; i++)
	{
		//copy pregame state over to post game
		memcpy(&postState, &preState, sizeof (struct gameState));

		//By disabling the call to shuffle() in tributeRefactor, we can test with expected knowledge of the top cards after
		//the discard is "shuffled" back into the deck.
		postState.discard[nextPlayer][preState.discardCount[nextPlayer]-1] = topCard[i];
		postState.discard[nextPlayer][preState.discardCount[nextPlayer]-2] = nextTopCard[i];

		//reset card names
		strcpy(firstCard, "");
		strcpy(secondCard, "");

		//change variables based on revealed cards
		//if top card is a treasure card
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

		//still discarding 2 cards total, only after post shuffle
		deckDiscard = 2;

		printf("-- TEST %d: nextPlayer deck count = 0, 1st card = %s, 2nd card = %s --\n", testCount + 1, firstCard, secondCard);

		//call the tribute card
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

		printf("Test: nextPlayer deck count = %d, expected = %d\t\tStatus: ", postState.deckCount[nextPlayer], preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard);
		if (postState.deckCount[nextPlayer] == preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard)
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

	//*************************************************************************************************************************************
	//set deck count of all other players equal to 0 and discard count to 1
	for ( i = 0; i < preState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			preState.deckCount[i] = 0;
			preState.discardCount[i] = 1;
		}
	}

	//test all single cards
	for (i = 0; i < 3; i++)
	{
		//copy pregame state over to post game
		memcpy(&postState, &preState, sizeof (struct gameState));

		//By disabling the call to shuffle() in tributeRefactor, we can test with expected knowledge of the top cards after
		//the discard is "shuffled" back into the deck.
		postState.discard[nextPlayer][preState.discardCount[nextPlayer]-1] = nextTopCard[i];

		//reset card names
		strcpy(firstCard, "");
		strcpy(secondCard, "");

		//change variables based on revealed cards
		//if top card is a treasure card
		if (nextTopCard[i] == gold)
		{
			netCoins = 2;
			strcpy(secondCard, "treasure");
		}
		else
		{
			netCoins = 0;
		}
		//if one of the cards is a victory card
		if (nextTopCard[i] == estate)
		{
			drawnCards = 2;
			strcpy(secondCard, "victory");
		}
		else
		{
			drawnCards = 0;
		}
		//if one of the cards is an action card
		if (nextTopCard[i] == baron)
		{
			netActions = 2;
			strcpy(secondCard, "action");
		}
		else
		{
			netActions = 0;
		}

		//only possible to discard 1 card
		deckDiscard = 1;

		printf("-- TEST %d: nextPlayer deck count = 0, discard count = 1, 1st card = %s --\n", testCount + 1, secondCard);

		//call the tribute card
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

		printf("Test: nextPlayer deck count = %d, expected = %d\t\tStatus: ", postState.deckCount[nextPlayer], preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard);
		if (postState.deckCount[nextPlayer] == preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard)
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

	//*************************************************************************************************************************************
	//set deck count of all other players equal to 1 and discard count to 0
	for ( i = 0; i < preState.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			preState.deckCount[i] = 0;
			preState.discardCount[i] = 1;
		}
	}

	//test all single cards
	for (i = 0; i < 3; i++)
	{
		//copy pregame state over to post game
		memcpy(&postState, &preState, sizeof (struct gameState));

		postState.deck[nextPlayer][postState.deckCount[nextPlayer]-1] = nextTopCard[i];

		//reset card names
		strcpy(firstCard, "");
		strcpy(secondCard, "");

		//change variables based on revealed cards
		//if top card is a treasure card
		if (nextTopCard[i] == gold)
		{
			netCoins = 2;
			strcpy(secondCard, "treasure");
		}
		else
		{
			netCoins = 0;
		}
		//if one of the cards is a victory card
		if (nextTopCard[i] == estate)
		{
			drawnCards = 2;
			strcpy(secondCard, "victory");
		}
		else
		{
			drawnCards = 0;
		}
		//if one of the cards is an action card
		if (nextTopCard[i] == baron)
		{
			netActions = 2;
			strcpy(secondCard, "action");
		}
		else
		{
			netActions = 0;
		}

		//only possible to discard 1 card
		deckDiscard = 1;

		printf("-- TEST %d: nextPlayer deck count = 1, discard count = 0, 1st card = %s --\n", testCount + 1, secondCard);

		//call the tribute card
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

		printf("Test: nextPlayer deck count = %d, expected = %d\t\tStatus: ", postState.deckCount[nextPlayer], preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard);
		if (postState.deckCount[nextPlayer] == preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard)
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