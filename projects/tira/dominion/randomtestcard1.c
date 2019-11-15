#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "baron"
#define NUMTESTS 1000

int main() {
	//seed rand
	srand(time(NULL));

	//success and fail counts
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

	//flag for test oracle
	int estateInHand;

	//two game states used to compare card effects
	struct gameState preState, postState;

	//initialize card array
	//i am deciding to keep the card array consistent for each test
	int k[10] = {adventurer, minion, ambassador, gardens, mine, remodel, smithy, tribute, baron, great_hall};

	printf("----------------- Testing Card: %s -----------------\n\n", TESTCARD);

	printf("THE FOLLOWING TESTS FAILED\n");
	printf("TestNum\tnumPlayers\tcurrentPlayer\thandCount\testateInHand\tcardEffectChoice\tTestStatus");

	//Randomize the gamestate
	for (i = 0; i < NUMTESTS; i++)
	{
		//randomize 1-4 players
		numPlayers = (rand() % 4) + 1;
		//randomize seed
		seed = rand() % 2000;
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
				if (preState.hand[currentPlayer][i] == estate)
				{
					preState.hand[currentPlayer][i] = mine;
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



		printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded + drawnCards);
		testCount++;
		if (postState.handCount[currentPlayer] == preState.handCount[currentPlayer] - discarded + drawnCards)
		{
			numSuccess++;
		}
		else
		{
			//printf("TEST #%d FAILED: incorrect handcount\n", testCount);
			//printf("TestNum\tnumPlayers\tcurrentPlayer\thandCount\testateInHand\tcardEffectChoice\tTestStatus");
			printf("%d\t%d\t%d\t%d\t%d\t%d\tincorrect handcount", testCount, numPlayers, currentPlayer, preState.handCount[currentPlayer], estateInHand, choice1);
			//printf("\tINPUTS:")
		}
		/*
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

		printf("Test: buys = %d, expected = %d\t\tStatus: ", postState.numBuys, preState.numBuys + netBuys);
		if (postState.numBuys == preState.numBuys + netBuys)
		{
			printf("SUCCESS\n");
			numSuccess++;
		}
		else
		{
			printf("FAIL\n");
			numFail++;
		}

		printf("Test: estate supply = %d, expected = %d\tStatus: ", postState.supplyCount[estate], preState.supplyCount[estate] + netSupply);
		if (postState.supplyCount[estate] == preState.supplyCount[estate] + netSupply)
		{
			printf("SUCCESS\n");
			numSuccess++;
		}
		else
		{
			printf("FAIL\n");
			numFail++;
		}

		printf("\n");*/

		//randomize hand size
	//randomize library size
	//randomize supply count
	//randomize player card effect choice
	}
	/*

	//*************************************************************************************************************
	// TEST 1: choice1 = 1 = discard estate, +4 gold
	printf("-- TEST 1: choice1 = 1 = discard estate, +4 gold --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on card effects
	choice1 = 1;
	discarded = 1;
	netCoins = 4;

	//call the card
	cardEffect(baron, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded + drawnCards);
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

	printf("Test: buys = %d, expected = %d\t\tStatus: ", postState.numBuys, preState.numBuys + netBuys);
	if (postState.numBuys == preState.numBuys + netBuys)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: estate supply = %d, expected = %d\tStatus: ", postState.supplyCount[estate], preState.supplyCount[estate] + netSupply);
	if (postState.supplyCount[estate] == preState.supplyCount[estate] + netSupply)
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
	// TEST 2: choice1 = 1, no estate card in hand
	printf("-- TEST 2: choice1 = 1, no estate card in hand --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on card effects
	choice1 = 1;
	discarded = 1;
	netCoins = 4;

	//modify hand to contain no estate card
	for ( i = 0; i < postState.handCount[currentPlayer]; i++)
	{
		if (postState.hand[currentPlayer][i] == estate)
		{
			postState.hand[currentPlayer][i] = mine;
		}
	}

	//call the card
	cardEffect(baron, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded + drawnCards);
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

	printf("Test: buys = %d, expected = %d\t\tStatus: ", postState.numBuys, preState.numBuys + netBuys);
	if (postState.numBuys == preState.numBuys + netBuys)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: estate supply = %d, expected = %d\tStatus: ", postState.supplyCount[estate], preState.supplyCount[estate] + netSupply);
	if (postState.supplyCount[estate] == preState.supplyCount[estate] + netSupply)
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
	// TEST 3: choice1 = 0 = do not discard estate, gain an estate
	printf("-- TEST 3: choice1 = 0 = do not discard estate, gain an estate --\n");

	//copy pregame state over to post game
	memcpy(&postState, &preState, sizeof (struct gameState));

	//change choice variables based on card effects
	choice1 = 0;
	discarded = 0;
	netCoins = 0;
	netSupply = -1;

	//call the card
	cardEffect(baron, choice1, choice2, choice3, &postState, handPos, &bonus);

	printf("Test: hand count = %d, expected = %d\tStatus: ", postState.handCount[currentPlayer], preState.handCount[currentPlayer] - discarded + drawnCards);
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

	printf("Test: buys = %d, expected = %d\t\tStatus: ", postState.numBuys, preState.numBuys + netBuys);
	if (postState.numBuys == preState.numBuys + netBuys)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("Test: estate supply = %d, expected = %d\tStatus: ", postState.supplyCount[estate], preState.supplyCount[estate] + netSupply);
	if (postState.supplyCount[estate] == preState.supplyCount[estate] + netSupply)
	{
		printf("SUCCESS\n");
		numSuccess++;
	}
	else
	{
		printf("FAIL\n");
		numFail++;
	}

	printf("\n");*/

	printf("Tests completed for %s.\n", TESTCARD);
	printf("%d out of %d tests passed.\n\n", numSuccess, testCount);

	return 0;
}