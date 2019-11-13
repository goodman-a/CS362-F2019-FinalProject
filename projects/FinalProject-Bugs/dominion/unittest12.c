/* 
 * Course: OSU CS 362 - Software Engineering II
 * Assignment: Final Project
 * Author: Alexander Goodman
 * Due Date: 03 December 2019
 * 
 * File: unittest12.c
 * 
 * File Description: Unit Test for the minion case in the cardEffect().
 * 
 * Function:
 *    int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
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
        // OR NOT SAY ANYTHING?
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

int MinionTest(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int num_players);


/* -- MAIN FUNCTION -- */
int main(int argc, char** argv){
  /* -- Variables for Comparison, Checks, and Vericiations -- */

  // Iterators
  int i;

  // setup/initialize paramters
  srand(time(0));
  int seed = rand();
  int player1, player2;
  int num_players;

  int minionReturn; 


  // Passed in gameplay values
  int card, handPos = 0, choice1 = 0, choice2 = 0, choice3=0, bonus=0;

  // Kingdom Cards
  int k[10] = {adventurer, council_room, tribute, gardens, mine, remodel, smithy, village, baron, great_hall};

  // Declare Game State
  struct gameState state;

    /* __________ TESTING TIME __________ */

  /* -- Test Overview -- */
  /* -- 
    1. No Choice Selected (choice1 & choice2 == false)
    2. choice1 
    3. choice2 & player2 Hand Count > 4
    4. choice2 & player2 Hand Count == 4
    5. choice2 & player2 Hand Count < 4
    6. choice2 & player1 & player2 Hand Coutnt < 4
    7. choice2: 3 playes (player2 Hand Count < 4 & player3 Hand Count > 4)
    8*. different handPos..
  -- */

  printf("\n********** Bug 12 (minion case) Unit Test **********\n");

  // Test Parameters
  card = minion;
  num_players = 2;
  player1 = 0;
  player2 = 1;

  /* -- Test 1 (No Choice Selection) -- */
  printf("_____ TEST #1 _____\n");

  choice1 = 0;
  choice2 = 0;
  bonus = 0;

  // Initialize Game and Set Player Hand Counts
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);
  state.handCount[player1] = 5;
  state.handCount[player2] = 5;

  // Generate Hands and set minion card in player1 first index
  for(i=0; i<num_players; i++)
  { HandGenerator(&state, i, state.handCount[i],0,treasure_map); }

  handPos = 0;
  state.hand[player1][handPos] = minion;

  minionReturn = MinionTest(card, choice1, choice2, choice3, &state, handPos, &bonus, num_players);
  if(minionReturn) { /* -- Placeholder -- */ }

  /* -- Test 2 (choice1) -- */
  printf("_____ TEST #2 _____\n");
 
  choice1 = 1;
  choice2 = 0;
  bonus = 0;

  // Initalize Game and Set Player Hand Counts
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);
  state.handCount[player1] = 5;
  state.handCount[player2] = 5;

  // Generate Hands and set minion card in player1 first index
  for(i=0; i<num_players; i++)
  { HandGenerator(&state, i, state.handCount[i],0,treasure_map); }

  handPos = 0;
  state.hand[player1][handPos] = minion;

  minionReturn = MinionTest(card, choice1, choice2, choice3, &state, handPos, &bonus, num_players);
  if(minionReturn) { /* -- FAULT -- */ }

  /* -- Test 3 (choice2: player2 handCount > 4) -- */
  printf("_____ TEST #3 _____\n");
  choice1 = 0;
  choice2 = 2;
  bonus = 0;

  // Initialize Game and Set Player Hand Counts
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);
  state.handCount[player1] = 5;
  state.handCount[player2] = 5;

  // Generate Hands and set minion card in player1 first index
  for(i=0; i<num_players; i++)
  { HandGenerator(&state, i, state.handCount[i],0,treasure_map); }

  handPos = 0;
  state.hand[player1][handPos] = minion;

  minionReturn = MinionTest(card, choice1, choice2, choice3, &state, handPos, &bonus, num_players);

  /* -- Test 4 (choice2: player2 handCount == 4) -- */
  printf("_____ TEST #4 _____\n");
  choice1 = 0;
  choice2 = 2;
  bonus = 0;

  // Initialize Game and Set Player Hand Counts
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);
  state.handCount[player1] = 5;
  state.handCount[player2] = 4;

  // Generate Hands and set minion card in player1 first index
  for(i=0; i<num_players; i++)
  { HandGenerator(&state, i, state.handCount[i],0,treasure_map); }

  handPos = 0;
  state.hand[player1][handPos] = minion;

  minionReturn = MinionTest(card, choice1, choice2, choice3, &state, handPos, &bonus, num_players);

  /* -- Test 5 (choice2: player2 handCount < 4) -- */
  printf("_____ TEST #5 _____\n");
  choice1 = 0;
  choice2 = 2;
  bonus = 0;

  // Initialize Game and Set Player Hand Counts
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);
  state.handCount[player1] = 5;
  state.handCount[player2] = 3;

  // Generate Hands and set minion card in player1 first index
  for(i=0; i<num_players; i++)
  { HandGenerator(&state, i, state.handCount[i],0,treasure_map); }

  handPos = 0;
  state.hand[player1][handPos] = minion;

  minionReturn = MinionTest(card, choice1, choice2, choice3, &state, handPos, &bonus, num_players);

  /* -- Test 6 (choice2: player1 & player2 handCount < 4) -- */
  printf("_____ TEST #6 _____\n");
  choice1 = 0;
  choice2 = 2;
  bonus = 0;

  // Initialize Game and Set Player Hand Counts
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);
  state.handCount[player1] = 3;
  state.handCount[player2] = 3;

  // Generate Hands and set minion card in player1 first index
  for(i=0; i<num_players; i++)
  { HandGenerator(&state, i, state.handCount[i],0,treasure_map); }

  handPos = 0;
  state.hand[player1][handPos] = minion;

  minionReturn = MinionTest(card, choice1, choice2, choice3, &state, handPos, &bonus, num_players);

  /* -- Test 7 (choice2: 3 players (player2 handCount <4 & player3 handCount > 4) -- */
  printf("_____ TEST #7 _____\n");

  choice1 = 0;
  choice2 = 2;
  bonus = 0;
  num_players = 3;

  // Initialize Game and Set Player Hand Counts
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);
  state.handCount[player1] = 3;
  state.handCount[player2] = 3;
  state.handCount[2] = 5;

  // Generate Hands and set minion card in player1 first index
  for(i=0; i<num_players; i++)
  { HandGenerator(&state, i, state.handCount[i],0,treasure_map); }

  handPos = 0;
  state.hand[player1][handPos] = minion;

  minionReturn = MinionTest(card, choice1, choice2, choice3, &state, handPos, &bonus, num_players);


  return 0;
}

/* -- Minion Card Case Unit Test Function -- */
int MinionTest(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int num_players)
{
  int z;
  int cardEffectReturn = -1;
  int flagFail = 0;
  int assertReturn;
  int player1 = 0;
  int bonus_start = state->coins;

  // Set-up Test Game State
  struct gameState testState;
  memcpy(&testState, state, sizeof(struct gameState));

  // Call cardEffect() for the remodel card
  cardEffectReturn = cardEffect(card, choice1, choice2,choice3, &testState, handPos, bonus);
  
  if(choice1)
  {
    // cardEffectReturn == 0
    if(cardEffectReturn != 0){flagFail=1; printf("FAIL: Minion Card Unexpected Return\n");}

    // +1 Action
    assertReturn = AssertTest((testState.numActions == state->numActions +1), "Player1: +1 Action");
    if(assertReturn){flagFail=1;printf("\tNumber of Actions: Current = %d vs. Expected = %d\n", testState.numActions, state->numActions +1);}

    // +2 Bonus
    assertReturn = AssertTest((testState.coins == bonus_start+2), "Player1: +2 Bonus");
    if(assertReturn) {flagFail = 1; printf("\tBonus Count: Current = %d vs. Exepected = %d\n", testState.coins, bonus_start+2);}


    // +1 Discard Count
    assertReturn = AssertTest((testState.discardCount[player1] == state->discardCount[player1]+1), "Player1: +1 Discard Count");
    if(assertReturn){flagFail = 1; printf("\tDiscard Count: Current = %d, Expected = %d\n", testState.discardCount[player1], state->discardCount[player1]+1);}

    //-1 Hand Count
    assertReturn = AssertTest((testState.handCount[player1] == state->handCount[player1]-1), "Player1: -1 Hand Count");
    if(assertReturn){flagFail = 1; printf("\tHand Count: Current = %d, Expected = %d\n", testState.handCount[player1], state->handCount[player1]-1);}
  }

  else if(choice2)
  {
    // cardEffectReturn == 0
    if(cardEffectReturn != 0){flagFail=1; printf("FAIL: Minion Card Unexpected Return\n");}

    /* -- Player -- */
    // +0 Bonus
    assertReturn = AssertTest((testState.coins == bonus_start), "Player1: +0 Bonus");
    if(assertReturn) {flagFail = 1; printf("\tBonus Count: Current = %d vs. Exepected = %d\n", testState.coins, bonus_start);}

    // Player 1: Test Hand Count <= 4
    assertReturn = AssertTest((testState.handCount[player1] <= 4), "Player1: Hand Count <= 4");
    if(assertReturn){flagFail = 1; printf("\tHand Count: Current = %d, Expected <= %d\n", testState.handCount[player1], 4);}

    // Player 1: Test Discard Count == State Hand Count
    assertReturn = AssertTest((testState.discardCount[player1] == state->handCount[player1]+state->discardCount[player1]), "Player1: +handCount Discard Count");
    if(assertReturn){flagFail = 1; printf("\tDiscard Count: Current = %d, Expected = %d\n", testState.discardCount[player1], state->handCount[player1]+state->discardCount[player1]);}

    /* -- Opponents -- */
    for(z=0; z<num_players; z++)
    {
      if(z != player1)
      {
        // Opponent Hand Counts <= 4
        assertReturn = AssertTest((testState.handCount[z] <= 4), "Opponent: Hand Count <= 4");
        if(assertReturn){flagFail = 1; printf("\tPlayer #%d - Hand Count: Current = %d, Expected <= %d\n", z, testState.handCount[z], 4);}

        // If Opponnent Hand Count is Greater Than 4 (discard and draw 4)
        if(state->handCount[z]>4)
        {
          //Test Discard Count == State Hand Count + State Discard Count
          assertReturn = AssertTest((testState.discardCount[z] == state->handCount[z]+state->discardCount[player1]), "Opponent: +handCount Discard Count");
          if(assertReturn){flagFail = 1; printf("\tDiscard Count: Current = %d, Expected = %d\n", testState.discardCount[z], state->handCount[z]+state->discardCount[z]);}
        }
        // Else Opponent Keeps Current Hand.
        else
        {
          // +0 Discard Count
          assertReturn = AssertTest((testState.discardCount[z] == state->discardCount[z]), "Opponent: +0 Discard Count");
          if(assertReturn){flagFail = 1; printf("\tDiscard Count: Current = %d, Expected = %d\n", testState.discardCount[z], state->discardCount[z]);}  
        }
        
      }
    }

  }

  // No Selection Made (choice1 & choice2 == false)
  else
  {
    // cardEffectReturn == -1
    if(cardEffectReturn != -1){flagFail=1; printf("FAIL: Minion Card Allowed Invalid Move (No Choice Selection)\n");}

    // +0 Discard Count (Should Fail Once discarCard() is properly fixed)
    assertReturn = AssertTest((testState.discardCount[player1] == state->discardCount[player1]), "Player1: +0 Discard Count");
    if(assertReturn){flagFail = 1; printf("\tDiscard Count: Current = %d, Expected = %d\n", testState.discardCount[player1], state->discardCount[player1]);}

  }

  if(flagFail)
  {
    printf("  *Test Information: \n");
    //printf("\tHand Count Before: Player1 = %d ; Player2 = %d\n",state->handCount[0], state->handCount[1]);
    //printf("\tHand Count After: Player1 = %d ; Player2 = %d\n",testState.handCount[0], testState.handCount[1]);
    printf("\tchoice1 = %d ; choice2 = %d\n",choice1, choice2);
    printf("\tNumber of Players = %d\n", num_players);
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




