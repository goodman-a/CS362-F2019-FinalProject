/************************************************************************************
** Author:	Cris Shumack
** Date:	12/03/2019
** Assignment:  CS 362 Final Project
** Description: Unit tests for the Mine card function. Tests Mine card's main
**		functions, as well as finds bugs.
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

	int *bonus = 0;
	int card = mine;
	int player1 = 0;
	int seed = 1024;
	int p1HandCount = 0;
	int p1DiscardCount = 0;
	int choice2SupplyCount = 0;
	int pCardCount = 0;

	//Gamestate 1 (G1) will test the baron card effect when the user choice is 1
	//and the user has an estate card in hand. G2 will test the baron card effect
	//when the user choice is 0 where they should gain an estate card. G3 will 
	//test baron card when the user choice is 1 but there is no estate in hand.
	struct gameState G1, G2, G3, G4;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	memset(&G3, 23, sizeof(struct gameState));
	memset(&G4, 23, sizeof(struct gameState));

	//Inititalizes G1 and use memcpy to initialize G2 and G3.
	initializeGame(2, k, seed, &G1);
	memcpy(&G2, &G1, sizeof(struct gameState));
	memcpy(&G3, &G1, sizeof(struct gameState));
	memcpy(&G4, &G1, sizeof(struct gameState));

	//Calls the gainCard function for each gamestate to ensure
	//they each have a treasure card in hand.
	gainCard(copper, &G1, 2, player1);
	gainCard(copper, &G2, 2, player1);
	gainCard(silver, &G3, 2, player1);
	gainCard(copper, &G4, 2, player1);

	G4.supplyCount[silver] = 0;
	G3.supplyCount[copper] = 45;

	printf("***************************UNIT TEST FOR BUG 01******************************\n");

	printf("              Begin Testing mineCardEffect() on G1 (choices: copper, silver):\n");

	printf("Return Success (0) Test: ");
	assertInt(0, cardEffect(card, copper, silver, -1, &G1, 0, bonus));

	p1HandCount = G1.handCount[player1];
	p1DiscardCount = G1.discardCount[player1];
	choice2SupplyCount = G1.supplyCount[silver];
	pCardCount = G1.playedCardCount;

	printf("\nExpected Hand Count: 6\n");
	printf("Actual Hand Count: %d\n", p1HandCount);
	printf("Hand Count Test: ");
	assertInt(p1HandCount, 6);

	printf("\nExpected Discard Count: 1\n");
	printf("Actual Discard Count: %d\n", p1DiscardCount);
	printf("Discard Count Test: ");
	assertInt(p1DiscardCount, 1);

	printf("\nExpected Played Card Count: 0\n");
	printf("Actual Played Card Count: %d\n", pCardCount);
	printf("Played Card Count Test: ");
	assertInt(pCardCount, 0);

	printf("\nExpected choice2 Supply Count: 39\n");
	printf("Actual choice2 Supply Count: %d\n", choice2SupplyCount);
	printf("choice2 Supply Count Test: ");
	assertInt(choice2SupplyCount, 39);

	printf("\n             Begin Testing baronCardEffect() on G2 (choices: copper, gold):\n");

	printf("Return Error (-1) Test: ");
	assertInt(-1, cardEffect(card, copper, gold, -1, &G2, 0, bonus));

	p1HandCount = G2.handCount[player1];
	p1DiscardCount = G2.discardCount[player1];
	choice2SupplyCount = G2.supplyCount[gold];
	pCardCount = G2.playedCardCount;
	
	printf("\nExpected Hand Count: 6\n");
	printf("Actual Hand Count: %d\n", p1HandCount);
	printf("Hand Count Test: ");
	assertInt(p1HandCount, 6);

	printf("\nExpected Discard Count: 0\n");
	printf("Actual Discard Count: %d\n", p1DiscardCount);
	printf("Discard Count Test: ");
	assertInt(p1DiscardCount, 0);

	printf("\nExpected Played Card Count: 0\n");
	printf("Actual Played Card Count: %d\n", pCardCount);
	printf("Played Card Count Test: ");
	assertInt(pCardCount, 0);

	printf("\nExpected choice2 Supply Count: 30\n");
	printf("Actual choice2 Supply Count: %d\n", choice2SupplyCount);
	printf("choice2 Supply Count Test: ");
	assertInt(choice2SupplyCount, 30);

	printf("\n             Begin Testing baronCardEffect() on G3 (choices: silver, copper):\n");

	printf("Return Success (0) Test: ");
	assertInt(0, cardEffect(card, silver, copper, -1, &G3, 0, bonus));

	p1HandCount = G3.handCount[player1];
	p1DiscardCount = G3.discardCount[player1];
	choice2SupplyCount = G3.supplyCount[copper];
	pCardCount = G3.playedCardCount;
	
	printf("\nExpected Hand Count: 6\n");
	printf("Actual Hand Count: %d\n", p1HandCount);
	printf("Hand Count Test: ");
	assertInt(p1HandCount, 6);

	printf("\nExpected Discard Count: 1\n");
	printf("Actual Discard Count: %d\n", p1DiscardCount);
	printf("Discard Count Test: ");
	assertInt(p1DiscardCount, 1);

	printf("\nExpected Played Card Count: 0\n");
	printf("Actual Played Card Count: %d\n", pCardCount);
	printf("Played Card Count Test: ");
	assertInt(pCardCount, 0);

	printf("\nExpected choice2 Supply Count: 44\n");
	printf("Actual choice2 Supply Count: %d\n", choice2SupplyCount);
	printf("choice2 Supply Count Test: ");
	assertInt(choice2SupplyCount, 44);

	printf("\n             Begin Testing baronCardEffect() on G4 (choices: copper, silver (none in supply)):\n");

	printf("Return Error (-1) Test: ");
	assertInt(-1, cardEffect(card, copper, silver, -1, &G4, 0, bonus));

	p1HandCount = G4.handCount[player1];
	p1DiscardCount = G4.discardCount[player1];
	choice2SupplyCount = G4.supplyCount[silver];
	pCardCount = G4.playedCardCount;
	
	printf("\nExpected Hand Count: 6\n");
	printf("Actual Hand Count: %d\n", p1HandCount);
	printf("Hand Count Test: ");
	assertInt(p1HandCount, 6);

	printf("\nExpected Discard Count: 1\n");
	printf("Actual Discard Count: %d\n", p1DiscardCount);
	printf("Discard Count Test: ");
	assertInt(p1DiscardCount, 1);

	printf("\nExpected Played Card Count: 0\n");
	printf("Actual Played Card Count: %d\n", pCardCount);
	printf("Played Card Count Test: ");
	assertInt(pCardCount, 0);

	printf("\nExpected choice2 Supply Count: 0\n");
	printf("Actual choice2 Supply Count: %d\n", choice2SupplyCount);
	printf("choice2 Supply Count Test: ");
	assertInt(choice2SupplyCount, 0);

	printf("\nTest completed!\n");

	return 0;
}
