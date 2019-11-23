/*******************************************************************************
* Name: Samantha Guilbeault
* Date: 11-16-2019
* Description: Contains unit tests for Bug02
* Bug02: Case tribute fails to discard the revealed cards back to the next player
*
* Test 1: Next player has 1 card total available for revealing
* Test 2: Next player has 2 different cards available for revealing
* Test 3: Next player has 2 of the same cards avaialbe for revealing
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

// source: http://www.dillonbhuff.com/?p=439
#define MY_ASSERT(x, y) if (!(x)) { printf("*FAILED TEST: %s\n", y); } else { printf("*PASSED TEST: %s\n", y); }


int main()
{
	// set game variables
	int seed = 50;
	int numPlayer = 2;

	// init test variables
	int card = tribute;
	struct gameState G;
	int *bonus = 0;
	int currentPlayer = 0;
	int nextPlayer = 1;

	int returnValue = -10;
	int discardCountBefore = -1;
	int deckCountBefore = -1;
	int revealedCards[2];

	// set card array
	int k[10] = { tribute, ambassador, feast, gardens, mine,
	remodel, smithy, village, baron, treasure_map };

	// init new game
	initializeGame(numPlayer, k, seed, &G);

	printf("\n********************************************************************************\n");
	printf("          Bug02 Unit Test - Tribute Fails to Discard Revealed Cards\n");
	printf("********************************************************************************\n\n");

	/***************************************** TEST 1 ****************************************/
	printf("-------- Test 1: Next player has 1 card revealed --------\n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	G.whoseTurn = currentPlayer;  // set current player to be 0
	G.deck[nextPlayer][0] = estate;  // put one card in deck
	deckCountBefore = 1;
	G.deckCount[nextPlayer] = deckCountBefore;  // set deck count to 1
	discardCountBefore = 0;
	G.discardCount[nextPlayer] = discardCountBefore;  // make sure next player has 0 cards in discard
	revealedCards[0] = estate;  // one card will be revealed
	revealedCards[1] = -1;

	// call function
	returnValue = cardEffect(card, -1, -1, -1, &G, -1, bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// one card taken from deck
	MY_ASSERT(G.deckCount[nextPlayer] == deckCountBefore - 1, "one card taken from deck");
	printf("  deck count: %d, expected: %d\n", G.deckCount[nextPlayer], deckCountBefore - 1);

	// one card returned to discard pile
	MY_ASSERT(G.discardCount[nextPlayer] == discardCountBefore + 1, "one card returned to discard pile");
	printf("  discard count: %d, expected: %d\n", G.discardCount[nextPlayer], discardCountBefore + 1);

	// returned card is the revealed card
	MY_ASSERT(G.discard[nextPlayer][0] == revealedCards[0], "returned card is the revealed card");
	printf("  returned card value: %d, expected: %d\n", G.discard[nextPlayer][0], revealedCards[0]);


	/***************************************** TEST 2 ****************************************/
	printf("\n");
	printf("-------- Test 2: Next player has 2 different cards revealed --------\n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	G.whoseTurn = currentPlayer;  // set current player to be 0
	G.deck[nextPlayer][0] = estate;  // put two different cards in deck
	G.deck[nextPlayer][1] = copper;
	deckCountBefore = 2;  // track deck count
	G.deckCount[nextPlayer] = deckCountBefore;  // set deck count to 2
	discardCountBefore = 0;  // track discard count
	G.discardCount[nextPlayer] = discardCountBefore;  // make sure next player has 0 cards in discard
	revealedCards[0] = G.deck[nextPlayer][1];  // track first revealed card
	revealedCards[1] = G.deck[nextPlayer][0];  // track second revealed card

	// call function
	returnValue = cardEffect(card, -1, -1, -1, &G, -1, bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// two cards taken from deck
	MY_ASSERT(G.deckCount[nextPlayer] == deckCountBefore - 2, "Two cards taken from deck");
	printf("  deck count: %d, expected: %d\n", G.deckCount[nextPlayer], deckCountBefore - 2);

	// two cards returned to discard pile
	MY_ASSERT(G.discardCount[nextPlayer] == discardCountBefore + 2, "two cards returned to discard pile");
	printf("  discard count: %d, expected: %d\n", G.discardCount[nextPlayer], discardCountBefore + 2);

	// returned cards are the revealed cards
	MY_ASSERT(G.discard[nextPlayer][0] == revealedCards[0], "first returned card is the first revealed card");
	printf("  first returned card value: %d, expected: %d\n", G.discard[nextPlayer][0], revealedCards[0]);

	MY_ASSERT(G.discard[nextPlayer][1] == revealedCards[1], "second returned card is the second revealed card");
	printf("  second returned card value: %d, expected: %d\n", G.discard[nextPlayer][1], revealedCards[1]);


	/***************************************** TEST 3 ****************************************/
	printf("\n");
	printf("-------- Test 3: Next player has 2 of the same cards revealed -------- \n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	G.whoseTurn = currentPlayer;  // set current player to be 0
	G.deck[nextPlayer][0] = estate;  // put two of the same cards in deck
	G.deck[nextPlayer][1] = estate;
	deckCountBefore = 2;  // track deck count
	G.deckCount[nextPlayer] = deckCountBefore;  // set deck count to 2
	discardCountBefore = 0;  // track discard count
	G.discardCount[nextPlayer] = discardCountBefore;  // make sure next player has 0 cards in discard
	revealedCards[0] = G.deck[nextPlayer][1];  // track first revealed card
	revealedCards[1] = G.deck[nextPlayer][0];  // track second revealed card

	// call function
	returnValue = cardEffect(card, -1, -1, -1, &G, -1, bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// two cards taken from deck
	MY_ASSERT(G.deckCount[nextPlayer] == deckCountBefore - 2, "Two cards taken from deck");
	printf("  deck count: %d, expected: %d\n", G.deckCount[nextPlayer], deckCountBefore - 2);

	// two cards returned to discard pile
	MY_ASSERT(G.discardCount[nextPlayer] == discardCountBefore + 2, "two cards returned to discard pile");
	printf("  discard count: %d, expected: %d\n", G.discardCount[nextPlayer], discardCountBefore + 2);

	// returned cards are the revealed cards
	MY_ASSERT(G.discard[nextPlayer][0] == revealedCards[0], "first returned card is the first revealed card");
	printf("  first returned card value: %d, expected: %d\n", G.discard[nextPlayer][0], revealedCards[0]);

	MY_ASSERT(G.discard[nextPlayer][1] == revealedCards[1], "second returned card is the second revealed card");
	printf("  second returned card value: %d, expected: %d\n", G.discard[nextPlayer][1], revealedCards[1]);

	printf("\nUnit Tests for Bug02 Complete\n\n");
	return 0;
}