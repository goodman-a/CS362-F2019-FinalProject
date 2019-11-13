/* 
 * Course: OSU CS 362 - Software Engineering II
 * Assignment: Final Project
 * Author: Alexander Goodman
 * Due Date: 03 December 2019
 * 
 * File: unittest06.c
 * 
 * File Description: Unit Test for the scoreFor().
 * 
 * Function:
 *   int scoreFor(int player, struct gameState *state)
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
void DisplayHand(struct gameState *state, int player, char* msg);
void DisplayDiscard(struct gameState *state, int player, char* msg);
void DisplayDeck(struct gameState *state, int player, char* msg);

int HandCardCount(struct gameState *state, int player, int choice1);
int DiscardCardCount(struct gameState *state, int player, int card);
int DeckCardCount(struct gameState *state, int player, int card);

int ScoreForTestA(struct gameState *state, int player);
int ScoreForTestB(struct gameState *state, int player);


/* -- MAIN FUNCTION -- */
int main(int argc, char** argv){
  /* -- Variables for Comparison, Checks, and Vericiations -- */

  // Iterators
  int i;

  // setup/initialize paramters
  srand(time(0));
  int seed = rand();
  int num_players = 2;
  int player = 0;

  int scoreReturn;

  // Kingdom Cards
  int k[10] = {adventurer, treasure_map, tribute, gardens, mine, remodel, sea_hag, village, baron, great_hall};

  // Declare Game State
  struct gameState state;

    /* __________ TESTING TIME __________ */

  /* -- Test Overview -- */
  /* -- 
    // note: fullDeckCount Needs to be fixed and refactored into 3 separate functions 

    Test Set A (Hand == Discard == Deck):
      1. No Victory Cards
      2. Only Copper & Estates (No Curse & No Gardens)
      3. Curse Added
      4. Gardens Added

    Test Set B (Varying Pile Size with Copper & Estate Mixture?):
      *note: setting last card in Hand = great_hall, Discard = duchy, and Deck = Province
      1. handCount = discardCount = deckCount (baseline)
      2. handCount < discardCount ; discardCount == deckCount
      3. handCount < discardCount ; discarCount < deckCount
      4. handCount < discardCount ; discardCount > deckCount
      5. All Piles are at 0
  -- */


  printf("\n********** Bug 06 (scoreFor()) Unit Test **********\n");

  printf("----- BUG 06 TEST SET A (HandCount == DiscardCount == DeckCount) -----\n");
  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Parameters
  state.handCount[player] = 5;
  state.discardCount[player] = 5;
  state.deckCount[player] = 5;

  // Fill Piles with Coppers!
  for(i=0; i<state.handCount[player]; i++)
  { state.hand[player][i] = copper; }
  for(i=0; i<state.discardCount[player]; i++)
  { state.discard[player][i] = copper; }
  for(i=0; i<state.deckCount[player]; i++)
  { state.deck[player][i] = copper; }

  // Set-up Test Game State
  struct gameState testState;
  memcpy(&testState, &state, sizeof(struct gameState));


  /* -- Test 1A (No Victory Cards Present) -- */
    printf("_____ TEST #1A _____\n");
  // Set-up Test Game State
  memset(&testState, 0, sizeof(struct gameState));
  memcpy(&testState, &state, sizeof(struct gameState));

  scoreReturn = ScoreForTestA(&testState, player);


  /* -- Test 2A (Only Copper, Estates, & Duchy) -- */
      printf("_____ TEST #2A _____\n");
  // Set-up Test Game State
  memset(&testState, 0, sizeof(struct gameState));
  memcpy(&testState, &state, sizeof(struct gameState));

  // Place Estates at Beginning & Duchy at End of Each Pile
  testState.hand[player][0] = estate;
  testState.hand[player][state.handCount[player]-1] = duchy;
  testState.discard[player][0] = estate;
  testState.discard[player][state.discardCount[player]-1] = duchy;
  testState.deck[player][0] = estate;
  testState.deck[player][state.deckCount[player]-1] = duchy;

  scoreReturn = ScoreForTestA(&testState, player);


  /* -- Test 3A (Curse Added) -- */
  printf("_____ TEST #3A _____\n");
  // Set-up Test Game State
  memset(&testState, 0, sizeof(struct gameState));
  memcpy(&testState, &state, sizeof(struct gameState));

  // Replace End with Curse
  testState.hand[player][state.handCount[player]-1] = curse;
  testState.discard[player][state.discardCount[player]-1] = curse;
  testState.deck[player][state.deckCount[player]-1] = curse;

  scoreReturn = ScoreForTestA(&testState, player);


  /* -- Test 4A (Gardens Added) -- */
  printf("_____ TEST #4A _____\n");
  // Set-up Test Game State
  memset(&testState, 0, sizeof(struct gameState));
  memcpy(&testState, &state, sizeof(struct gameState));

  // Replace End with Gardens
  testState.hand[player][state.handCount[player]-1] = gardens;
  testState.discard[player][state.discardCount[player]-1] = gardens;
  testState.deck[player][state.deckCount[player]-1] = gardens;

  scoreReturn = ScoreForTestA(&testState, player);


  printf("----- BUG 06 TEST SET B (Varying Pile Sizes) -----\n");

  /* -- Test 1B (handCount = discardCount = deckCount) */
  printf("_____ TEST #1B _____\n");

  // Initialize Game
  memset(&state, 23, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Parameters
  state.handCount[player] = 5;
  state.discardCount[player] = 5;
  state.deckCount[player] = 5;

  // Run the Test
  scoreReturn = ScoreForTestB(&state, player);
  if(scoreReturn) { /* Nothing for Now */ }


  /* -- Test 2B (handCount < discardCount ; discardCount == deckCount) */
  printf("_____ TEST #2B _____\n");

  // Initialize Game
  memset(&state, 23, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Parameters
  state.handCount[player] = 5;
  state.discardCount[player] = 10;
  state.deckCount[player] = 10;

  // Run the Test
  scoreReturn = ScoreForTestB(&state, player);


  /* -- Test 3B (handCount < discardCount ; discardCount < deckCount) */
  printf("_____ TEST #3B _____\n");

  // Initialize Game
  memset(&state, 23, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Parameters
  state.handCount[player] = 5;
  state.discardCount[player] = 8;
  state.deckCount[player] = 12;

  // Run the Test
  scoreReturn = ScoreForTestB(&state, player);


  /* -- Test 4B (handCount < discardCount ; discardCount > deckCount) */
  printf("_____ TEST #4B _____\n");

  // Initialize Game
  memset(&state, 23, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Parameters
  state.handCount[player] = 5;
  state.discardCount[player] = 12;
  state.deckCount[player] = 9;

  // Run the Test
  scoreReturn = ScoreForTestB(&state, player);


  /* -- Test 5B (All Piles Are Empty) */
  printf("_____ TEST #5B _____\n");

  // Initialize Game
  memset(&state, 23, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Parameters
  state.handCount[player] = 0;
  state.discardCount[player] = 0;
  state.deckCount[player] = 0;

  // Run the Test
  scoreReturn = ScoreForTestB(&state, player);

  return 0;  // end of main
}


/* -- ScoreForTestA -- */
// Assert Tests with Varying Differnt Victory Cards
int ScoreForTestA(struct gameState *state, int player)
{
  // Variables 
  int flagFail = 0, assertReturn;
  int score_hand ,score_discard, score_deck, total_score, scoreForReturn;
  int total_cards = state->handCount[player] + state->discardCount[player] + state->deckCount[player];

  // Calculations for Comparisons
  score_hand = (HandCardCount(state, player, curse)*-1) + (HandCardCount(state, player, estate)*1) + (HandCardCount(state, player, duchy)*3) + (HandCardCount(state, player, province)*6) + (HandCardCount(state, player, great_hall)*1) + (HandCardCount(state, player, gardens)*(total_cards/10));
  score_discard = (DiscardCardCount(state, player, curse)*-1) + (DiscardCardCount(state, player, estate)*1) + (DiscardCardCount(state, player, duchy)*3) + (DiscardCardCount(state, player, province)*6) + (DiscardCardCount(state, player, great_hall)*1) + (DiscardCardCount(state, player, gardens)*(total_cards/10));
  score_deck = (DeckCardCount(state, player, curse)*-1) + (DeckCardCount(state, player, estate)*1) + (DeckCardCount(state, player, duchy)*3) + (DeckCardCount(state, player, province)*6) + (DeckCardCount(state, player, great_hall)*1) + (DeckCardCount(state, player, gardens)*(total_cards/10));

  total_score = score_hand + score_discard + score_deck;

  scoreForReturn = scoreFor(player, state);

  // Return Value Comparison
  assertReturn = AssertTest(scoreForReturn == total_score, "Total Player Score");
  if(assertReturn) { flagFail = 1; printf("\tscoreFor() Calculated: %d vs. Expected: %d\n", scoreForReturn, total_score); }

  if(flagFail)
  {
    printf("  *Test Information:\n");
    printf("\tTotal Cards: %d ; Hand Count: %d ; Discard Count: %d ; Deck Count: %d\n",total_cards,state->handCount[player],state->discardCount[player],state->deckCount[player] );
    printf("\tCalculated Scores: Hand = %d ; Discard = %d ; Deck = %d\n",score_hand, score_discard, score_deck);
    printf("\t"); DisplayHand(state, player, "Player1");
    printf("\t"); DisplayDiscard(state, player, "Player1");
    printf("\t"); DisplayDeck(state, player, "Player1");
  }


  return flagFail;
}


/* -- ScoreForTestB -- */
// Assert Tests with Varying Pile Sizes
int ScoreForTestB(struct gameState *state, int player)
{
  // Variables 
  int flagFail = 0, assertReturn;
  int score_hand ,score_discard, score_deck, total_score, scoreForReturn;
  int total_cards = state->handCount[player] + state->discardCount[player] + state->deckCount[player];
  int i;

  // Fill Piles with Coppers!
  for(i=0; i<state->handCount[player]; i++)
  { state->hand[player][i] = copper; }
  for(i=0; i<state->discardCount[player]; i++)
  { state->discard[player][i] = copper; }
  for(i=0; i<state->deckCount[player]; i++)
  { state->deck[player][i] = copper; }

  // Set Last Cards in Each Pile to a Specific Card for Checking Offsets
  state->hand[player][state->handCount[player]-1] = great_hall;  // +1
  state->discard[player][state->discardCount[player]-1] = duchy; // +3
  state->deck[player][state->deckCount[player]-1] = province;    // +6

   // Calculations for Comparisons
  score_hand = (HandCardCount(state, player, curse)*-1) + (HandCardCount(state, player, estate)*1) + (HandCardCount(state, player, duchy)*3) + (HandCardCount(state, player, province)*6) + (HandCardCount(state, player, great_hall)*1) + (HandCardCount(state, player, gardens)*(total_cards/10));
  score_discard = (DiscardCardCount(state, player, curse)*-1) + (DiscardCardCount(state, player, estate)*1) + (DiscardCardCount(state, player, duchy)*3) + (DiscardCardCount(state, player, province)*6) + (DiscardCardCount(state, player, great_hall)*1) + (DiscardCardCount(state, player, gardens)*(total_cards/10));
  score_deck = (DeckCardCount(state, player, curse)*-1) + (DeckCardCount(state, player, estate)*1) + (DeckCardCount(state, player, duchy)*3) + (DeckCardCount(state, player, province)*6) + (DeckCardCount(state, player, great_hall)*1) + (DeckCardCount(state, player, gardens)*(total_cards/10));

  total_score = score_hand + score_discard + score_deck;

  scoreForReturn = scoreFor(player, state);

  // Return Value Comparison
  assertReturn = AssertTest(scoreForReturn == total_score, "Total Player Score");
  if(assertReturn) { flagFail = 1; printf("\tscoreFor() Calculated: %d vs. Expected: %d\n", scoreForReturn, total_score); }

  if(flagFail)
  {
    printf("  *Test Information:\n");
    printf("\tTotal Cards: %d ; Hand Count: %d ; Discard Count: %d ; Deck Count: %d\n",total_cards,state->handCount[player],state->discardCount[player],state->deckCount[player] );
    printf("\tCalculated Scores: Hand = %d ; Discard = %d ; Deck = %d\n",score_hand, score_discard, score_deck);
    printf("\t"); DisplayHand(state, player, "Player1");
    printf("\t"); DisplayDiscard(state, player, "Player1");
    printf("\t"); DisplayDeck(state, player, "Player1");
  }

  return flagFail;
}


/* -- Helper Functions -- */

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

// Count of a specific card in discard.
int DiscardCardCount(struct gameState *state, int player, int card)
{
    int count = 0;
    int i;

    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == card) count++;
    }

    return count;
}

// Count of a specific card in deck.
int DeckCardCount(struct gameState *state, int player, int card)
{
    int count = 0;
    int i;

    for (i = 0; i < state->deckCount[player]; i++)
    {
        if (state->deck[player][i] == card) count++;
    }

    return count;
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




