/***************************************************************************************
** Author:      Cris Shumack
** Date:        12/03/2019
** Assignment:  CS 362 Final Project
** Description: Unit tests for the Ambassador card function. Tests Ambassador
**		card's main functions, as well as finds bugs.
***************************************************************************************/

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
		printf("PASSED\n");
	else 
		printf("FAILED\n");
}

int main()
{
	int k[10] = { adventurer, ambassador, feast, gardens, mine
		      , remodel, smithy, village, baron, great_hall };

	int card = ambassador;
	int *bonus = 0;
	int player1 = 0;
	int player2 = 1;
	int seed = 1024;

	// Set Hand Position of the Ambassador Card and hand location of selected card to be trashed
	int handPos = 0;
	int choice1 = handPos +1;

	// Create Gamestates
	struct gameState G1, G2, G3, G4, G5;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	memset(&G3, 23, sizeof(struct gameState));
	memset(&G4, 23, sizeof(struct gameState));
	memset(&G5, 23, sizeof(struct gameState));

	//Inititalizes G1 and use memcpy to initialize G2, G3, G4 and G5.
	initializeGame(2, k, seed, &G1);
	memcpy(&G2, &G1, sizeof(struct gameState));
	memcpy(&G3, &G1, sizeof(struct gameState));
	memcpy(&G4, &G1, sizeof(struct gameState));
	memcpy(&G5, &G1, sizeof(struct gameState));

    // set-up Gamestate 1 
	handPos = 0;
	choice1 = handPos +1;
	G1.hand[player1][handPos] = ambassador;
	G1.hand[player1][choice1] = village;
	gainCard(village, &G1, 2, player1);

	G1.discardCount[player2] = 0;
	G1.supplyCount[village] = 10;

	// set-up Gamestate 2
	handPos = 0;
	choice1 = handPos +1;
	G2.hand[player1][handPos] = ambassador;
	G2.hand[player1][choice1] = village;
	gainCard(village, &G2, 2, player1);
	gainCard(village, &G2, 2, player1);

	G2.discardCount[player2] = 0;
	G2.supplyCount[village] = 10;

	// set-up Gamestate 3
	G3.hand[player1][choice1] = feast;

	// set-up Gamestate 4
	gainCard(village, &G4, 2, player1);

	// set-up Gamestate 5
	G5.hand[player1][choice1] = feast;

	// Print out hand for debugging check.
	/*
	int j = 0;
	for(j=0;j<G1.handCount[player1]; j++)
	  { printf("(%d)",G1.hand[player1][j]); }
	*/

	printf("***************************UNIT TEST FOR BUG 11******************************\n");
	
	printf("               Begin Testing ambassadorCardEffect() on G1:\n");
	
	printf("\nReturn Success (0) Test: ");
	assertInt(0, cardEffect(card, choice1, 1, -1, &G1, handPos, bonus));

	printf("\nPlayer1 Expected Hand Count: 4\n");
	printf("Player1 Actual Hand Count: %d\n", G1.handCount[player1]);
	printf("Hand Count Test: ");
	assertInt(G1.handCount[player1], 4);
	printf("\n");

	printf("Player2 Expected Discard Count: 1\n");
	printf("Player2 Actual Discard Count: %d\n", G1.discardCount[player2]);
	printf("Discard Count Test: ");
	assertInt(G1.discardCount[player2], 1);
	printf("\n");

	printf("choice1 Supply Count: 11\n");
	printf("choice1 Supply Count: %d\n", G1.supplyCount[village]);
	printf("Supply Count Test: ");
	assertInt(G1.supplyCount[village], 10);
	printf("\n");

	printf("\n                Begin Testing ambassadorCardEffect() on G2:\n");
	
	printf("\nReturn Success (0) Test: ");
	assertInt(0, cardEffect(card, choice1, 2, -1, &G2, 0, bonus));

	printf("\nPlayer1 Expected Hand Count: 4\n");
	printf("Player1 Actual Hand Count: %d\n", G2.handCount[player1]);
	printf("Hand Count Test: ");
	assertInt(G2.handCount[player1], 4);
	printf("\n");

	printf("Player2 Expected Discard Count: 2\n");
	printf("Player2 Actual Discard Count: %d\n", G2.discardCount[player2]);
	printf("Discard Count Test: ");
	assertInt(G2.discardCount[player2], 1);
	printf("\n");

	printf("choice1 Supply Count: 12\n");
	printf("choice1 Supply Count: %d\n", G2.supplyCount[village]);
	printf("Supply Count Test: ");
	assertInt(G2.supplyCount[village], 11);
	printf("\n");

	printf("\n                Begin Testing ambassadorCardEffect() on G3:\n");

	printf("\nReturn Error (-1) Test: ");
	assertInt(-1, cardEffect(card, choice1, 1, -1, &G3, 0, bonus));

	printf("\n                Begin Testing ambassadorCardEffect() on G4:\n");

	printf("\nReturn Error (-1) Test: ");
	assertInt(-1, cardEffect(card, choice1, 3, -1, &G4, 0, bonus));

	printf("\n                Begin Testing ambassadorCardEffect() on G5:\n");

	printf("\nReturn Error (-1) Test: ");
	assertInt(-1, cardEffect(card, choice1, 3, -1, &G5, 0, bonus));
	
	printf("\nTest completed!\n");

	return 0;
}
