#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "tribute"
#define NUMTESTS 2000

int main() {
	//seed rand
	srand(time(NULL));

	//success and test counts
	int numSuccess = 0;
	int testCount = 0;

	int i;

	//initialize relevant card variables
	//most variables remain here for reusability, but unused variables are commented out
	//some of these values will change depending on the test and card effect choice
	int drawnCards = 0;
	int discarded = 0;
	int netCoins = 0;
	int shuffledCards = 0;
	int netActions = 0;
	int deckDiscard = 0;

	//initialize cardEffect() variables
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	//variables for initializeGame()
	int seed;
	int numPlayers;
	int currentPlayer;

	//index of player to the left
	int nextPlayer;

	//two game states used to compare card effects
	struct gameState preState, postState;

	//initialize card array
	//i am deciding to keep the card array consistent for each test
	int k[10] = {adventurer, minion, ambassador, gardens, mine, remodel, smithy, tribute, baron, great_hall};

	//top card array and placeholders
	int topCard[3] = {gold, estate, baron};
	int firstCard;
	int secondCard;

	printf("----------------- Testing Card: %s -----------------\n\n", TESTCARD);

	//Randomize the gamestate
	for (i = 0; i < NUMTESTS; i++)
	{
		//randomize 2-4 players
		numPlayers = (rand() % 3) + 2;
		//randomize seed
		seed = rand() % 9999999;
		//randomize current player
		currentPlayer = rand() % numPlayers;
		//set the index of the player to the left
		if (currentPlayer == numPlayers - 1)
		{
			nextPlayer = 0;
		}
		else
		{
			nextPlayer = currentPlayer + 1;
		}

		//initialize a game using pregame state
		initializeGame(numPlayers, k, seed, &preState);

		//randomize hand count, 1-5, so that there will always be at least 1 card in hand
		//since playing tribute is not possible if it was not in your hand
		preState.handCount[currentPlayer] = (rand() % 5) + 1;

		//randomize deck size and discard count of next player
		//the total deck and discard count will always equal 10
		preState.deckCount[nextPlayer] = rand() % 10;
		preState.discardCount[nextPlayer] = 10 - preState.deckCount[nextPlayer];


		if (preState.deckCount[nextPlayer] > 1)
		{
			//randomize top 2 cards
			firstCard = topCard[rand() % 3];
			secondCard = topCard[rand() % 3];
			preState.deck[nextPlayer][preState.deckCount[nextPlayer]-1] = firstCard;
			preState.deck[nextPlayer][preState.deckCount[nextPlayer]-2] = secondCard;

			//2 cards get discarded off top of deck
			deckDiscard = 2;
		}
		if (preState.deckCount[nextPlayer] == 1)
		{
			//By disabling the call to shuffle() in tributeRefactor, we can test with expected knowledge of the top card after
			//the discard is "shuffled" back into the deck.
			firstCard = topCard[rand() % 3];
			secondCard = topCard[rand() % 3];
			preState.deck[nextPlayer][preState.deckCount[nextPlayer]-1] = firstCard;
			preState.discard[nextPlayer][preState.discardCount[nextPlayer]-1] = secondCard;

			//2 total cards gets disarded off top of deck after shuffle
			deckDiscard = 2;
		}
		if (preState.deckCount[nextPlayer] == 0)
		{
			//By disabling the call to shuffle() in tributeRefactor, we can test with expected knowledge of the top cards after
			//the discard is "shuffled" back into the deck.
			firstCard = topCard[rand() % 3];
			secondCard = topCard[rand() % 3];
			preState.discard[nextPlayer][preState.discardCount[nextPlayer]-1] = firstCard;
			preState.discard[nextPlayer][preState.discardCount[nextPlayer]-2] = secondCard;

			//2 cards gets disarded off top of deck after shuffle
			deckDiscard = 2;
		}

		//here we change our card effect variables depending on the first and second cards
		//if one of the cards is a treasure card
		if (firstCard == gold)
		{
			netCoins = 2;
		}
		if (secondCard == gold)
		{
			netCoins = 2;
		}
		if (firstCard != gold && secondCard != gold)
		{
			netCoins = 0;
		}
		//if one of the cards is a victory card
		if (firstCard == estate)
		{
			drawnCards = 2;
		}
		if (secondCard == estate)
		{
			drawnCards = 2;
		}
		if (firstCard != estate && secondCard != estate)
		{
			drawnCards = 0;
		}
		//if one of the cards is an action card
		if (firstCard == baron)
		{
			netActions = 2;
		}
		if (secondCard == baron)
		{
			netActions = 2;
		}
		if (firstCard != baron && secondCard != baron)
		{
			netActions = 0;
		}

		//copy pregame state over to post game
		memcpy(&postState, &preState, sizeof (struct gameState));

		//call the card
		cardEffect(tribute, choice1, choice2, choice3, &postState, handPos, &bonus);

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
			printf("TEST #%d FAILED: current player incorrect deckcount\n", testCount);
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

		//test actions
		testCount++;
		if (postState.numActions == preState.numActions + netActions)
		{
			numSuccess++;
		}
		else
		{
			printf("TEST #%d FAILED: incorrect actions\n", testCount);
		}

		if (preState.deckCount[nextPlayer] > 1)
		{
			//for next player deck that has at least 2 cards
			testCount++;
			if (postState.deckCount[nextPlayer] == preState.deckCount[nextPlayer] - deckDiscard)
			{
				numSuccess++;
			}
			else
			{
				printf("TEST #%d FAILED: next player incorrect deckcount\n", testCount);
			}
		}
		else if ( preState.deckCount[nextPlayer] == 1 || preState.deckCount[nextPlayer] == 0)
		{
			//for next player deck that has 1 or 0 cards
			testCount++;
			if (postState.deckCount[nextPlayer] == preState.deckCount[nextPlayer] + preState.discardCount[nextPlayer] - deckDiscard)
			{
				numSuccess++;
			}
			else
			{
				printf("TEST #%d FAILED: next player incorrect deckcount\n", testCount);
			}
		}
	}

	printf("\n");

	printf("Tests completed for %s.\n", TESTCARD);
	printf("%d out of %d tests passed.\n\n", numSuccess, testCount);

	return 0;
}