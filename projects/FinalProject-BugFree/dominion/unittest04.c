/* 
 * Course: OSU CS 362 - Software Engineering II
 * Assignment: Final Project
 * Author: Alexander Goodman
 * Due Date: 03 December 2019
 * 
 * File: unittest04.c
 * 
 * File Description: Unit Test for the remodel case statement in the cardEffect Function.
 * 
 * Function:
 *   int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
 * 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>


/* -- ASSERT FUNCTION -- */
int AssertTest(int pass, char* msg)
{
    if(!pass)
    {
        printf("FAIL: %s\n", msg);
        return 1;
    }
    else
    {
        printf("PASS: %s\n", msg);
        return 0;
    }
    
}


/* -- Helper Function Prototypes -- */
void HandGenerator(struct gameState *state, int player, int size, int min, int max);
void DiscardGenerator(struct gameState *state, int player, int size, int min, int max);
void DeckGenerator(struct gameState *state, int player, int size, int min, int max);

void DisplayHand(struct gameState *state, int player, char* msg);
void DisplayDiscard(struct gameState *state, int player, char* msg);
void DisplayDeck(struct gameState *state, int player, char* msg);

int HandCardCount(struct gameState *state, int player, int choice1);
int RemodelTest(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int* bonus);



/* -- MAIN FUNCTION -- */
int main(int argc, char** argv){
  /* -- Variables for Comparison, Checks, and Vericiations -- */

  // Iterators
  //int i,j;

  // setup/initialize paramters
  srand(time(0));
  int seed = rand();
  int player1 = 0;
  int num_players = 2;

  int remodelReturn; 


  // Passed in gameplay values
  int card, handPos = 0, choice1 = 0, choice2 = 0, choice3=0, bonus=0;

  // Kingdom Cards
  int k[10] = {adventurer, council_room, tribute, gardens, mine, remodel, smithy, village, baron, great_hall};

  // Declare Game State
  struct gameState state;

    /* __________ TESTING TIME __________ */

  /* -- Test Overview -- */
  /* -- 
    1. choice1 + 2 < choice2    --> choice1=copper ; choice2=silver
    2. choice1 + 2 == choice2   --> choice1=silver ; choice2=silver
    3. choice1 + 2 > choice2    --> choice1=copper ; choice2=estate
    4. choice1 + 2 >= choice2 w/ choice2 supply count at 0
  -- */


  printf("\n********** Bug 04 (Remodel Card) Unit Test **********\n");

  /* -- Test 1 (choice1 + 2 < choice 2) -- */
  printf("_____ TEST #1 _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  card = remodel;
  remodelReturn = 0;

  // Set-up Hand Parameters and choice Parameters & Supply Counts
  state.handCount[player1] = 5;
  HandGenerator(&state, player1,state.handCount[player1], 0, treasure_map);
  handPos = 0;
  choice1 = 1;
  choice2 = silver;
  choice3 = 0;  // Only used as an input for cardEffect function. Does not get executed within remodel case
  state.hand[player1][handPos] = remodel;
  state.hand[player1][choice1] = copper;
  state.supplyCount[choice2] = 8;

  // Call Remodel Card Test
  remodelReturn = RemodelTest(card, choice1, choice2, choice3, &state, handPos, &bonus);

  // If there was a fault detected then print out test parameter information
  if(remodelReturn)
  { /* -- Nothing for Now -- */ }

  /* -- Test 2 (choice1 + 2 == choice 2) -- */
  printf("_____ TEST #2 _____\n");
  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  card = remodel;
  remodelReturn = 0;

  // Set-up Hand Parameters and choice Parameters & Supply Counts
  state.handCount[player1] = 5;
  HandGenerator(&state, player1,state.handCount[player1], 0, treasure_map);
  handPos = 0;
  choice1 = 1;
  choice2 = silver;
  choice3 = 0;  // Only used as an input for cardEffect function. Does not get executed within remodel case
  state.hand[player1][handPos] = remodel;
  state.hand[player1][choice1] = silver;
  state.supplyCount[choice2] = 8;

  // Call Remodel Card Test
  remodelReturn = RemodelTest(card, choice1, choice2, choice3, &state, handPos, &bonus);

  
  /* -- Test 3 (choice1 + 2 > choice 2) -- */
  printf("_____ TEST #3 _____\n");
  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  card = remodel;
  remodelReturn = 0;

  // Set-up Hand Parameters and choice Parameters & Supply Counts
  state.handCount[player1] = 5;
  HandGenerator(&state, player1,state.handCount[player1], 0, treasure_map);
  handPos = 0;
  choice1 = 1;
  choice2 = estate;
  choice3 = 0;  // Only used as an input for cardEffect function. Does not get executed within remodel case
  state.hand[player1][handPos] = remodel;
  state.hand[player1][choice1] = copper;
  state.supplyCount[choice2] = 8;

  // Call Remodel Card Test
  remodelReturn = RemodelTest(card, choice1, choice2, choice3, &state, handPos, &bonus);
  

  /* -- Test 4 (choice1 + 2 >= choice 2 w/ choice2 supply at 0) -- */ 
  printf("_____ TEST #4 _____\n");
  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  card = remodel;
  remodelReturn = 0;

  // Set-up Hand Parameters and choice Parameters & Supply Counts
  state.handCount[player1] = 5;
  HandGenerator(&state, player1,state.handCount[player1], 0, treasure_map);
  handPos = 0;
  choice1 = 1;
  choice2 = estate;
  choice3 = 0;  // Only used as an input for cardEffect function. Does not get executed within remodel case
  state.hand[player1][handPos] = remodel;
  state.hand[player1][choice1] = copper;
  state.supplyCount[choice2] = 0;

  // Call Remodel Card Test
  remodelReturn = RemodelTest(card, choice1, choice2, choice3, &state, handPos, &bonus);



  return 0;
}

/* -- Remodel Card Case Unit Test Function -- */
int RemodelTest(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
{
  int cardEffectReturn = -1;
  int flagFail = 0;
  int assertReturn;
  int player = 0;
    // Set-up Test Game State
  struct gameState testState;
  memcpy(&testState, state, sizeof(struct gameState));

  // Call cardEffect() for the remodel card
  cardEffectReturn = cardEffect(card, choice1, choice2,choice3, &testState, handPos, bonus);

  // Invalid Selections
  if(getCost(state->hand[player][choice1]) +2 < getCost(choice2))
  {
    // Check Return Status
    if(cardEffectReturn != -1){flagFail=1; printf("Remodel Card Accepted Invalid Selections\n");}

    // Assert Tests...

    // +0 Hand Count
    assertReturn = AssertTest((testState.handCount[player] == state->handCount[player]), "+0 Hand Count");
    if(assertReturn){flagFail = 1; printf("\tHand Count: Current = %d, Expected = %d\n", testState.handCount[player], state->handCount[player]);}

    // +0 Discard Count
    assertReturn = AssertTest((testState.discardCount[player] == state->discardCount[player]), "+0 Discard Count");
    if(assertReturn){flagFail = 1; printf("\tDiscard Count: Current = %d, Expected = %d\n", testState.discardCount[player], state->discardCount[player]);}

    // +0 Trashed Count

    // +0 choice2 Supply Count
    assertReturn = AssertTest((supplyCount(choice2, &testState) == supplyCount(choice2, state)), "+0 choice2 Supply Count");
    if(assertReturn){flagFail = 1; printf("\tchoice2 Supply Count: Current= %d, Expected = %d\n", supplyCount(choice2, &testState), supplyCount(choice2, state));}    


  }

  // Valid Selections
  else
  {
    // Check Return Status
    if(cardEffectReturn != 0){flagFail=1; printf("Remodel Card Selection Issue\n");}

    // -2 Hand Count
    assertReturn = AssertTest((testState.handCount[player] == state->handCount[player]-2), "-2 Hand Count (remodel & choice2)");
    if(assertReturn){flagFail = 1; printf("\tHand Count: Current = %d, Expected = %d\n", testState.handCount[player], state->handCount[player]-2);}

    // +2 Discard Count
    assertReturn = AssertTest((testState.discardCount[player] == state->discardCount[player]+2), "+2 Discard Count (remodel & choice2)");
    if(assertReturn){flagFail = 1; printf("\tDiscard Count: Current = %d, Expected = %d\n", testState.discardCount[player], state->discardCount[player]+2);}

    // +1 Trashed Count

    // -1 choice2 Supply Count (if supply is not already at zero)
    if(testState.supplyCount[choice2] <= 0)
    {
      assertReturn = AssertTest((supplyCount(choice2, &testState) == supplyCount(choice2, state)), "choice2 Supply Count Already Empty");
      if(assertReturn){flagFail = 1; printf("\tchoice2 Supply Count: Current= %d, Expected = %d\n", supplyCount(choice2, &testState), supplyCount(choice2, state));}  
    }
    else
    {
      assertReturn = AssertTest((supplyCount(choice2, &testState) == supplyCount(choice2, state)-1), "-1 choice2 Supply Count");
      if(assertReturn){flagFail = 1; printf("\tchoice2 Supply Count: Current= %d, Expected = %d\n", supplyCount(choice2, &testState), supplyCount(choice2, state)-1);}  
    }
  }
  // If Fault Detected then Print Out More Information
  if(flagFail)
  {
    printf("  *Test Information: \n");
    printf("\tChoice 1: %d ; Choice 2: %d\n", state->hand[player][choice1], choice2);
    printf("\tChoice 1 Value: %d ; Choice 2 Value: %d\n", getCost(state->hand[player][choice1]), getCost(choice2));   
  }


  return flagFail;
}

/* -- Helper Functions -- */

// Random Hand Generator 
void HandGenerator(struct gameState *state, int player, int size, int min, int max)
{
  int i;
  if(min > max)
  {
      int temp = min;
      min = max;
      max = temp;
  }

  for(i=0; i<size; i++)
  {
      state->hand[player][i] = (rand()%(max-min+1))+min;
  }

  return;
}

// Random Discard Generator 
void DiscardGenerator(struct gameState *state, int player, int size, int min, int max)
{
  int i;
  if(min > max)
  {
      int temp = min;
      min = max;
      max = temp;
  }

  for(i=0; i<size; i++)
  {
      state->discard[player][i] = (rand()%(max-min+1))+min;
  }

  return;
}

// Random Deck Generator 
void DeckGenerator(struct gameState *state, int player, int size, int min, int max)
{
  int i;
  if(min > max)
  {
      int temp = min;
      min = max;
      max = temp;
  }

  for(i=0; i<size; i++)
  {
      state->deck[player][i] = (rand()%(max-min+1))+min;
  }

  return;
}


// Display Cards in Hand, Discard, and Deck Piles
void DisplayHand(struct gameState *state, int player, char* msg)
{
    int m;
    printf("%s Hand Pile: ", msg);
    for (m=0; m<state->handCount[player]; m++) {
        printf("(%d)", state->hand[player][m]);
    }
    printf("\n");
}

void DisplayDiscard(struct gameState *state, int player, char* msg)
{
    int m;
    printf("%s Discard Pile: ", msg);
    for (m=0; m<state->discardCount[player]; m++) {
        printf("(%d)", state->discard[player][m]);
    }
    printf("\n");
}

void DisplayDeck(struct gameState *state, int player, char* msg)
{
    int m;
    printf("%s Deck Pile: ", msg);
    for (m=0; m<state->deckCount[player]; m++) {
        printf("(%d)", state->deck[player][m]);
    }
    printf("\n");
}  

// Count of a specific card in hand.
int HandCardCount(struct gameState *state, int player, int card)
{
    int count = 0;
    int i;

    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == card) count++;
    }

    return count;
}





