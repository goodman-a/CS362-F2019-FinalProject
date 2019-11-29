/*******************************************************************************
* Name: Samantha Guilbeault
* Date: 11-16-2019
* Description: Contains unit tests for Bug08
* Bug02: Case tribute reward loop overruns revealed card array
*
* Test 1: Next player reveals 0 cards
* Test 2: Next player reveals 1 treasure card
* Test 3: Next player reveals 1 province and 1 action card
* Test 4: Next player reveals 2 of the same treasure cards
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
	int bonus = 0;
	int currentPlayer = 0;
	int nextPlayer = 1;

	int returnValue = -10;
	int nextDeckCountBefore = -1;
	int revealedCards[2];
	int coinsBefore = -1;
	int handCountBefore = -1;
	int actionsBefore = -1;

	// set card array
	int k[10] = { tribute, ambassador, feast, gardens, mine,
	remodel, smithy, village, baron, treasure_map };

	// init new game
	initializeGame(numPlayer, k, seed, &G);

	printf("\n********************************************************************************\n");
	printf("       Bug08 Unit Test - Tribute Reward Loop Overrruns Revealed Card Array\n");
	printf("********************************************************************************\n\n");

	/***************************************** TEST 1 ****************************************/
	printf("-------- Test 1: Next player reveals 0 cards --------\n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	G.whoseTurn = currentPlayer;  // set current player to be 0
	nextDeckCountBefore = 0;  // make sure no cards are revealed
	G.deckCount[nextPlayer] = nextDeckCountBefore;  // set deck count to 0
	G.discardCount[nextPlayer] = 0;  // set discard count to 0
	revealedCards[0] = -1;  // zero cards will be revealed
	revealedCards[1] = -1;
	coinsBefore = G.coins;  // track coins
	handCountBefore = G.handCount[currentPlayer];  // track hand count
	actionsBefore = G.numActions;  // track actions


	// call function
	returnValue = cardEffect(card, -1, -1, -1, &G, -1, &bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// no cards are revealed
	MY_ASSERT(G.deckCount[nextPlayer] == nextDeckCountBefore, "no cards revealed");
	printf("  next player's deck count: %d, expected: %d\n", G.deckCount[nextPlayer], nextDeckCountBefore);

	// no rewards gained
	MY_ASSERT(G.coins + bonus == coinsBefore, "no coins gained");
	printf("  coins: %d, expected: %d\n", G.coins + bonus, coinsBefore);
	MY_ASSERT(G.handCount[currentPlayer] == handCountBefore, "no cards gained");
	printf("  hand count: %d, expected: %d\n", G.handCount[currentPlayer], handCountBefore);
	MY_ASSERT(G.numActions == actionsBefore, "no actions gained");
	printf("  actions: %d, expected: %d\n", G.numActions, actionsBefore);


	/***************************************** TEST 2 ****************************************/
	printf("\n");
	printf("-------- Test 2: Next player reveals 1 treasure card --------\n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	bonus = 0;  // reset bonus
	G.whoseTurn = currentPlayer;  // set current player to be 0
	nextDeckCountBefore = 1;  // make sure 1 card is revealed
	G.deckCount[nextPlayer] = nextDeckCountBefore;  // set deck count to 1
	G.deck[nextPlayer][0] = copper;
	G.discardCount[nextPlayer] = 0;  // set discard count to 0
	revealedCards[0] = G.deck[nextPlayer][0];  // card in deck will be revealed
	revealedCards[1] = -1;
	coinsBefore = G.coins;  // track coins
	handCountBefore = G.handCount[currentPlayer];  // track hand count
	actionsBefore = G.numActions;  // track actions


	// call function
	returnValue = cardEffect(card, -1, -1, -1, &G, -1, &bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// one card is revealed
	MY_ASSERT(G.deckCount[nextPlayer] == nextDeckCountBefore - 1, "one card revealed");
	printf("  next player's deck count: %d, expected: %d\n", G.deckCount[nextPlayer], nextDeckCountBefore - 1);

	// revealed card is a treasure - copper
	MY_ASSERT(G.discard[nextPlayer][0] == revealedCards[0], "revealed card is a copper");
	printf("  revealed card value: %d, expected: %d\n", G.discard[nextPlayer][0], revealedCards[0]);

	// exactly 2 coins are gained
	MY_ASSERT(G.coins + bonus == coinsBefore + 2, "two coins gained");
	printf("  coins: %d, expected: %d\n", G.coins + bonus, coinsBefore + 2);

	// no other rewards are gained
	MY_ASSERT(G.handCount[currentPlayer] == handCountBefore, "no cards gained");
	printf("  hand count: %d, expected: %d\n", G.handCount[currentPlayer], handCountBefore);
	MY_ASSERT(G.numActions == actionsBefore, "no actions gained");
	printf("  actions: %d, expected: %d\n", G.numActions, actionsBefore);


	/***************************************** TEST 3 ****************************************/
	printf("\n");
	printf("-------- Test 3: Next player reveals 1 province and 1 action card -------- \n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	//// set variables for this test
	bonus = 0;  // reset bonus
	G.whoseTurn = currentPlayer;  // set current player to be 0
	nextDeckCountBefore = 2;  // make sure 2 cards are revealed
	G.deckCount[nextPlayer] = nextDeckCountBefore;  // set deck count to 2
	G.deck[nextPlayer][0] = estate;
	G.deck[nextPlayer][1] = smithy;
	G.discardCount[nextPlayer] = 0;  // set discard count to 0
	revealedCards[0] = G.deck[nextPlayer][1];  // top card in deck is first revealed
	revealedCards[1] = G.deck[nextPlayer][0];  // bottom card in deck is second revealed
	coinsBefore = G.coins;  // track coins
	handCountBefore = G.handCount[currentPlayer];  // track hand count
	actionsBefore = G.numActions;  // track actions

	// call function
	returnValue = cardEffect(card, -1, -1, -1, &G, -1, &bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// two cards are revealed
	MY_ASSERT(G.deckCount[nextPlayer] == nextDeckCountBefore - 2, "two cards revealed");
	printf("  next player's deck count: %d, expected: %d\n", G.deckCount[nextPlayer], nextDeckCountBefore - 2);

	// first revealed card is matches top of deck - smithy
	MY_ASSERT(G.discard[nextPlayer][0] == revealedCards[0], "first revealed card is a smithy");
	printf("  first revealed card value: %d, expected: %d\n", G.discard[nextPlayer][0], revealedCards[0]);

	// second revealed card matches bottom of deck - estate
	MY_ASSERT(G.discard[nextPlayer][1] == revealedCards[1], "second revealed card is an estate");
	printf("  second revealed card value: %d, expected: %d\n", G.discard[nextPlayer][1], revealedCards[1]);

	// no coins are gained
	MY_ASSERT(G.coins + bonus == coinsBefore, "no coins gained");
	printf("  coins: %d, expected: %d\n", G.coins + bonus, coinsBefore);

	// two cards are gained
	MY_ASSERT(G.handCount[currentPlayer] == handCountBefore + 2, "two cards gained");
	printf("  hand count: %d, expected: %d\n", G.handCount[currentPlayer], handCountBefore + 2);

	// two actions are gained
	MY_ASSERT(G.numActions == actionsBefore + 2, "two actions gained");
	printf("  actions: %d, expected: %d\n", G.numActions, actionsBefore + 2);

	/***************************************** TEST 4 ****************************************/
	printf("\n");
	printf("-------- Test 4: Next player reveals 2 of the same treasure cards -------- \n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	//// set variables for this test
	bonus = 0;  // reset bonus
	G.whoseTurn = currentPlayer;  // set current player to be 0
	nextDeckCountBefore = 2;  // make sure 2 cards are revealed
	G.deckCount[nextPlayer] = nextDeckCountBefore;  // set deck count to 2
	G.deck[nextPlayer][0] = copper;  // make both cards the same
	G.deck[nextPlayer][1] = copper;
	G.discardCount[nextPlayer] = 0;  // set discard count to 0
	revealedCards[0] = G.deck[nextPlayer][1];  // top card in deck is first revealed
	revealedCards[1] = G.deck[nextPlayer][0];  // bottom card in deck is second revealed
	coinsBefore = G.coins;  // track coins
	handCountBefore = G.handCount[currentPlayer];  // track hand count
	actionsBefore = G.numActions;  // track actions

	// call function
	returnValue = cardEffect(card, -1, -1, -1, &G, -1, &bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// two cards are revealed
	MY_ASSERT(G.deckCount[nextPlayer] == nextDeckCountBefore - 2, "two cards revealed");
	printf("  next player's deck count: %d, expected: %d\n", G.deckCount[nextPlayer], nextDeckCountBefore - 2);

	// first revealed card is matches top of deck - copper
	MY_ASSERT(G.discard[nextPlayer][0] == revealedCards[0], "first revealed card is a copper");
	printf("  first revealed card value: %d, expected: %d\n", G.discard[nextPlayer][0], revealedCards[0]);

	// second revealed card matches bottom of deck - copper
	MY_ASSERT(G.discard[nextPlayer][1] == revealedCards[1], "second revealed card is an copper");
	printf("  second revealed card value: %d, expected: %d\n", G.discard[nextPlayer][1], revealedCards[1]);

	// only two coins are gained
	MY_ASSERT(G.coins + bonus == coinsBefore + 2, "only 2 coins gained");
	printf("  coins: %d, expected: %d\n", G.coins + bonus, coinsBefore + 2);

	// no other rewards gained
	MY_ASSERT(G.handCount[currentPlayer] == handCountBefore, "no cards gained");
	printf("  hand count: %d, expected: %d\n", G.handCount[currentPlayer], handCountBefore);
	MY_ASSERT(G.numActions == actionsBefore, "no actions gained");
	printf("  actions: %d, expected: %d\n", G.numActions, actionsBefore);

	printf("\nUnit Tests for Bug08 Complete\n\n");
	return 0;
}
