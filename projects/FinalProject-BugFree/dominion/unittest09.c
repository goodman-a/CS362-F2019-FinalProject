/************************************************************************************
** Author:	Cris Shumack
** Date:	12/03/2019
** Assignment:  CS 362 Final Project
** Description: Unit tests for the various card functions. Tests the functions'
**		effects that give players bonus coins.
************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//Simple function that compares integers and prints PASSED if
//they are equal or FAILED if not.
void assertInt(int a, int b)
{
	if (a == b)
		printf("PASSED");
	else
		printf("FAILED");
}

int main()
{
	int k[10] = { adventurer, council_room, feast, gardens, mine
			  , remodel, smithy, village, baron, great_hall };

	int player1 = 0;
	int player2 = 1;
	int seed = 1024;
	int i;
	
	struct gameState G1, G2, G3, G4, G5, G6;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	memset(&G3, 23, sizeof(struct gameState));
	memset(&G4, 23, sizeof(struct gameState));
	memset(&G5, 23, sizeof(struct gameState));
	memset(&G6, 23, sizeof(struct gameState));

	//Inititalizes G1 and use memcpy to initialize G2 and G3.
	initializeGame(2, k, seed, &G1);
	memcpy(&G2, &G1, sizeof(struct gameState));
	memcpy(&G3, &G1, sizeof(struct gameState));
	memcpy(&G4, &G1, sizeof(struct gameState));
	memcpy(&G5, &G1, sizeof(struct gameState));
	memcpy(&G6, &G1, sizeof(struct gameState));

	G3.deck[player2][8] = silver;
	G3.deck[player2][9] = copper;

	for (i = 0; i < G1.handCount[player1]; i++)
		G1.hand[player1][i] = estate;

	for (i = 0; i < G2.handCount[player1]; i++)
		G2.hand[player1][i] = estate;

	for (i = 0; i < G3.handCount[player1]; i++)
		G3.hand[player1][i] = estate;
	
	for (i = 0; i < G4.handCount[player1]; i++)
		G4.hand[player1][i] = estate;

	for (i = 0; i < G5.handCount[player1]; i++)
		G5.hand[player1][i] = estate;

	for (i = 0; i < G6.handCount[player1]; i++)
		G6.hand[player1][i] = estate;

	G1.hand[player1][0] = baron;
	G2.hand[player1][0] = minion;
	G3.hand[player1][0] = tribute;
	G4.hand[player1][0] = steward;
	G5.hand[player1][0] = embargo;
	G6.hand[player1][0] = salvager;

	G1.coins = 0;
	G2.coins = 0;
	G3.coins = 0;
	G4.coins = 0;
	G5.coins = 0;
	G6.coins = 0;

	printf("%d\n", handCard(G1.handCount[player1] - 1, &G1));

	printf("***************************UNIT TEST FOR BUG 01******************************\n");

	printf("              Begin Testing Baron case on G1:\n");

	printf("Return Success (0) Test: ");
	assertInt(0, playCard(0, 1, -1, -1, &G1));

	printf("\nExpected Coins: 4\n");
	printf("Actual Coins: %d\n", G1.coins);
	printf("Coins Test: ");
	assertInt(G1.coins, 4);

	printf("\n             Begin Testing Minion case on G2:\n");

	printf("Return Success (0) Test: ");
	assertInt(0, playCard(0, 1, -1, -1, &G2));

	printf("\nExpected Coins: 2\n");
	printf("Actual Coins: %d\n", G2.coins);
	printf("Coins Test: ");
	assertInt(G2.coins, 2);

	printf("\n             Begin Testing Tribute case on G3:\n");

	printf("Return Success (0) Test: ");
	assertInt(0, playCard(0, -1, -1, -1, &G3));

	printf("\nExpected Coins: 4\n");
	printf("Actual Coins: %d\n", G3.coins);
	printf("Coins Test: ");
	assertInt(G3.coins, 4);

	printf("\n             Begin Testing Steward case on G4:\n");

	printf("Return Success (0) Test: ");
	assertInt(0, playCard(0, 2, -1, -1, &G4));

	printf("\nExpected Coins: 2\n");
	printf("Actual Coins: %d\n", G4.coins);
	printf("Coins Test: ");
	assertInt(G4.coins, 2);

	printf("\n             Begin Testing Embargo case on G5:\n");

	printf("Return Success (0) Test: ");
	assertInt(0, playCard(0, 1, -1, -1, &G5));

	printf("\nExpected Coins: 2\n");
	printf("Actual Coins: %d\n", G5.coins);
	printf("Coins Test: ");
	assertInt(G5.coins, 2);

	printf("\n             Begin Testing Salvager case on G6:\n");

	printf("Return Success (0) Test: ");
	assertInt(0, playCard(0, estate, -1, -1, &G6));

	printf("\nExpected Coins: 2\n");
	printf("Actual Coins: %d\n", G6.coins);
	printf("Coins Test: ");
	assertInt(G6.coins, 2);

	printf("\nTest completed!\n");

	return 0;
}
