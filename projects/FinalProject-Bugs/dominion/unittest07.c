/*******************************************************************************
* Name: Samantha Guilbeault
* Date: 11-17-2019
* Description: Contains unit tests for Bug07
* Bug07: Case feast makes invalid alteration of player's coin count
*
* Test 1: Player has 0 coins and chooses to gain card of value 5
* Test 2: Player has 3 coins and chooses to gain card of value 6
* Test 3: Player has 5 coins and chooses to gain card of value 4
* Test 4: Player has 8 coins and chooses to gain card of value 5
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
	int card = feast;
	int choice1 = -1;
	struct gameState G;
	int handPos = -1;
	int *bonus = 0;

	int currentPlayer = 0;
	int coinsBefore = -1;
	int discardCountBefore = -1;
	int returnValue = -10;

	// set card array
	int k[10] = { tribute, ambassador, feast, gardens, mine,
	remodel, smithy, village, baron, adventurer };

	// init new game
	initializeGame(numPlayer, k, seed, &G);

	printf("\n********************************************************************************\n");
	printf("  Bug07 Unit Test - Case Feast Makes Invalid Alteration of Player's Coin Count\n");
	printf("********************************************************************************\n\n");

	/***************************************** TEST 1 ****************************************/
	printf("------- Test 1: Player has 0 coins and chooses to gain card of value 5 -------\n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	G.whoseTurn = currentPlayer;  // set current player to be 0
	G.hand[currentPlayer][0] = feast;  // make sure player has a feast card in hand
	G.coins = 0;  // set coin count to 0
	coinsBefore = G.coins;  // track coins
	choice1 = mine;  // select card that costs 5
	G.supplyCount[mine] = 10;  // make sure supply has mine cards
	discardCountBefore = G.discardCount[currentPlayer];  // track hand count

	// call function
	returnValue = cardEffect(card, choice1, -1, -1, &G, handPos, bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// gained card goes to discard pile - makes sure gain was successful
	MY_ASSERT(G.discardCount[currentPlayer] == discardCountBefore + 1, "discard pile gains one card");
	printf("  discard count: %d, expected: %d\n", G.discardCount[currentPlayer], discardCountBefore + 1);

	// coin count stays the same
	MY_ASSERT(G.coins == coinsBefore, "coin count stays the same");
	printf("  coin count: %d, expected: %d\n", G.coins, coinsBefore);


	/***************************************** TEST 2 ****************************************/
	printf("\n");
	printf("------- Test 2: Player has 3 coins and chooses to gain card of value 6 -------\n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	G.whoseTurn = currentPlayer;  // set current player to be 0
	G.hand[currentPlayer][0] = feast;  // make sure player has a feast card in hand
	G.coins = 3;  // set coin count to 3
	coinsBefore = G.coins;  // track coins
	choice1 = adventurer;  // select card that costs 6
	G.supplyCount[adventurer] = 10;  // make sure supply has adventurer cards
	discardCountBefore = G.discardCount[currentPlayer];  // track hand count

	// call function
	returnValue = cardEffect(card, choice1, -1, -1, &G, handPos, bonus);

	// return value is valid
	MY_ASSERT(returnValue == -1, "return value is valid");
	printf("  return value: %d, expected: -1\n", returnValue);

	// no card gained
	MY_ASSERT(G.discardCount[currentPlayer] == discardCountBefore, "no card gained");
	printf("  discard count: %d, expected: %d\n", G.discardCount[currentPlayer], discardCountBefore);

	// coin count stays the same
	MY_ASSERT(G.coins == coinsBefore, "coin count stays the same");
	printf("  coin count: %d, expected: %d\n", G.coins, coinsBefore);


	/***************************************** TEST 3 ****************************************/
	printf("\n");
	printf("------- Test 3: Player has 5 coins and chooses to gain card of value 4 -------\n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	G.whoseTurn = currentPlayer;  // set current player to be 0
	G.hand[currentPlayer][0] = feast;  // make sure player has a feast card in hand
	G.coins = 5;  // set coin count to 3
	coinsBefore = G.coins;  // track coins
	choice1 = baron;  // select card that costs 4
	G.supplyCount[baron] = 10;  // make sure supply has baron cards
	discardCountBefore = G.discardCount[currentPlayer];  // track hand count

	// call function
	returnValue = cardEffect(card, choice1, -1, -1, &G, handPos, bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// one card gained
	MY_ASSERT(G.discardCount[currentPlayer] == discardCountBefore + 1, "one card gained");
	printf("  discard count: %d, expected: %d\n", G.discardCount[currentPlayer], discardCountBefore + 1);

	// coin count stays the same
	MY_ASSERT(G.coins == coinsBefore, "coin count stays the same");
	printf("  coin count: %d, expected: %d\n", G.coins, coinsBefore);


	/***************************************** TEST 4 ****************************************/
	printf("\n");
	printf("------- Test 4: Player has 8 coins and chooses to gain card of value 5 -------\n");

	memset(&G, 23, sizeof(struct gameState)); // clear game
	initializeGame(numPlayer, k, seed, &G);  // init new game

	// set variables for this test
	G.whoseTurn = currentPlayer;  // set current player to be 0
	G.hand[currentPlayer][0] = feast;  // make sure player has a feast card in hand
	G.coins = 8;  // set coin count to 8
	coinsBefore = G.coins;  // track coins
	choice1 = tribute;  // select card that costs 5
	G.supplyCount[tribute] = 10;  // make sure supply has tribute cards
	discardCountBefore = G.discardCount[currentPlayer];  // track hand count

	// call function
	returnValue = cardEffect(card, choice1, -1, -1, &G, handPos, bonus);

	// return value is valid
	MY_ASSERT(returnValue == 0, "return value is valid");
	printf("  return value: %d, expected: 0\n", returnValue);

	// one card gained
	MY_ASSERT(G.discardCount[currentPlayer] == discardCountBefore + 1, "one card gained");
	printf("  discard count: %d, expected: %d\n", G.discardCount[currentPlayer], discardCountBefore + 1);

	// coin count stays the same
	MY_ASSERT(G.coins == coinsBefore, "coin count stays the same");
	printf("  coin count: %d, expected: %d\n", G.coins, coinsBefore);

	printf("\nUnit Tests for Bug07 Complete\n\n");
	return 0;
}