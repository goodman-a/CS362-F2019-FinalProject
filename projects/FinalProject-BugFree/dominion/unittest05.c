/* 
 * Course: OSU CS 362 - Software Engineering II
 * Assignment: Final Project 
 * Author: Alexander Goodman
 * Due Date: 03 December 2019
 * 
 * File: unittest05.c
 * 
 * File Description: Unit Test for the isGameOver().
 * 
 * Function:
 *   int isGameOver(struct gameState *state);
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
void DisplayEmptySupply(struct gameState *state);
void DisplayHand(struct gameState *state, int player, char* msg);
void DisplayDiscard(struct gameState *state, int player, char* msg);
void DisplayDeck(struct gameState *state, int player, char* msg);


/* -- MAIN FUNCTION -- */
int main(int argc, char** argv){
  /* -- Variables for Comparison, Checks, and Vericiations -- */

  // Iterators
  //int i,j;

  // setup/initialize paramters
  srand(time(0));
  int seed = rand();
  int num_players = 2;

  int isGameOverReturn, assertReturn;

  // Kingdom Cards
  int k[10] = {adventurer, treasure_map, tribute, gardens, mine, remodel, sea_hag, village, baron, great_hall};

  // Declare Game State
  struct gameState state;

    /* __________ TESTING TIME __________ */

  /* -- Test Overview -- */
  /* -- 
    // note: isGameOver() returns 1 if it finds the game to be over and 0 otherwise
    1. 2 Supplies are empty (not including Treasure Map, Sea Hag, Curse, or Province)
    2. Province supply is empty
    3. 3 supplies are empty (not including Treasure Map, Sea Hag, Curse, or Province)
    4. 3 supplies are empty including curse (MINIMUM)
    5. 3 supplies are empty including Sea Hag
    6. 3 supplies are empty including Treasure Map (MAXIMUM)
    7. 4 supplies are empty including Treasure Map
  -- */


  printf("\n********** Bug 05 (isGameover()) Unit Test **********\n");

  /* -- Test 1 (2 Supplies are empty (not including Treasure Map, Sea Hag, Curse, or Province)) -- */
  printf("_____ TEST #1 _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  state.supplyCount[mine] = 0;
  state.supplyCount[tribute] = 0;

  // Run isGameOver() and check the return value
  isGameOverReturn = isGameOver(&state);
  
  // // Game is Not Over (Expect Return 0)
  assertReturn = AssertTest((isGameOverReturn == 0), "2 Empty Supplies");
  if(assertReturn){DisplayEmptySupply(&state);}


  /* -- Test 2 (Province Supply is Empty) -- */
  printf("_____ TEST #2 _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  state.supplyCount[province] = 0;

  // Run isGameOver() and check the return value
  isGameOverReturn = isGameOver(&state);
  
  // // Game is Not Over (Expect Return 0)
  assertReturn = AssertTest((isGameOverReturn == 1), "Province Supply is Empty");
  if(assertReturn){DisplayEmptySupply(&state);}


  /* -- Test 3 (3 Supplies are empty (not including Treasure Map, Sea Hag, Curse, or Province)) -- */
  printf("_____ TEST #3 _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  state.supplyCount[mine] = 0;
  state.supplyCount[tribute] = 0;
  state.supplyCount[copper] = 0;

  // Run isGameOver() and check the return value
  isGameOverReturn = isGameOver(&state);
  
  // // Game is Not Over (Expect Return 0)
  assertReturn = AssertTest((isGameOverReturn == 1), "3 Empty Supplies");
  if(assertReturn){DisplayEmptySupply(&state);}


  /* -- Test 4 (3 Supplies are empty including Curse) -- */
  printf("_____ TEST #4 _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  state.supplyCount[mine] = 0;
  state.supplyCount[tribute] = 0;
  state.supplyCount[curse] = 0;

  // Run isGameOver() and check the return value
  isGameOverReturn = isGameOver(&state);
  
  // // Game is Not Over (Expect Return 0)
  assertReturn = AssertTest((isGameOverReturn == 1), "3 Empty Supplies (including Curse)");
  if(assertReturn){DisplayEmptySupply(&state);}

  /* -- Test 5 (3 Supplies are empty including Sea Hag) -- */
  printf("_____ TEST #5 _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  state.supplyCount[mine] = 0;
  state.supplyCount[tribute] = 0;
  state.supplyCount[sea_hag] = 0;

  // Run isGameOver() and check the return value
  isGameOverReturn = isGameOver(&state);
  
  // // Game is Not Over (Expect Return 0)
  assertReturn = AssertTest((isGameOverReturn == 1), "3 Empty Supplies (including Sea Hag)");
  if(assertReturn){DisplayEmptySupply(&state);}


  /* -- Test 6 (3 Supplies are empty including Treasure Map) -- */
  printf("_____ TEST #6 _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  state.supplyCount[mine] = 0;
  state.supplyCount[tribute] = 0;
  state.supplyCount[treasure_map] = 0;

  // Run isGameOver() and check the return value
  isGameOverReturn = isGameOver(&state);
  
  // // Game is Not Over (Expect Return 0)
  assertReturn = AssertTest((isGameOverReturn == 1), "3 Empty Supplies (including Treasure Map)");
  if(assertReturn){DisplayEmptySupply(&state);}

  /* -- Test 7 (4 Supplies are empty including Treasure Map) -- */
  printf("_____ TEST #7 _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Test Parameters
  state.supplyCount[mine] = 0;
  state.supplyCount[tribute] = 0;
  state.supplyCount[copper] = 0;
  state.supplyCount[treasure_map] = 0;

  // Run isGameOver() and check the return value
  isGameOverReturn = isGameOver(&state);
  
  // // Game is Not Over (Expect Return 0)
  assertReturn = AssertTest((isGameOverReturn == 1), "4 Empty Supplies (including Treasure Map)");
  if(assertReturn){DisplayEmptySupply(&state);}


  return 0;
}


/* -- Helper Functions -- */

// Display All the Card Piles that are Empty
void DisplayEmptySupply(struct gameState *state)
{
  int i = 0;
  while(i<=treasure_map)
  {
    if(state->supplyCount[i] == 0)
    {
      printf("\tEnum Card %d Supply is Empty\n", i);
    }

    i++;
  }

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






