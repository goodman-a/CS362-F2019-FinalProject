/* 
 * Course: OSU CS 362 - Software Engineering II
 * Assignment: Final ProjectAssignment 3 Learn How to Create Unit Tests
 * Author: Alexander Goodman
 * Due Date: 03 December 2019
 * 
 * File: unittest06.c
 * 
 * File Description: Unit Test for the scoreFor().
 * 
 * Function:
 *   int scoreFor (int player, struct gameState *state)
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
void DisplayEmptySupply(struct gameState *state);
void HandGenerator(struct gameState *state, int player, int size, int min, int max);
void DiscardGenerator(struct gameState *state, int player, int size, int min, int max);
void DeckGenerator(struct gameState *state, int player, int size, int min, int max);

void DisplayHand(struct gameState *state, int player, char* msg);
void DisplayDiscard(struct gameState *state, int player, char* msg);
void DisplayDeck(struct gameState *state, int player, char* msg);

int HandCardCount(struct gameState *state, int player, int choice1);
int DiscardCardCount(struct gameState *state, int player, int card);
int DeckCardCount(struct gameState *state, int player, int card);
int HandCardCount2(struct gameState *state, int player, int choice1, int handPos);
int CheckShuffle(struct gameState *state_old, struct gameState *state_new, int player);  // retVal == 1 good, retVal <1 no shuffle

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
  //int total_cards = 0;
  //int score_hand, score_discard, score_deck;
  //int total_score;

  int scoreReturn;

  // Kingdom Cards
  int k[10] = {adventurer, treasure_map, tribute, gardens, mine, remodel, sea_hag, village, baron, great_hall};

  // victory cards
  //int v[6] = {curse, estate, duchy, province, great_hall, gardens};

  // Declare Game State
  struct gameState state;

    /* __________ TESTING TIME __________ */

  /* -- Test Overview -- */
  /* -- 
    // note: fullDeckCount Needs to be fixed andrefactored into 3 separate functions 
    // Need asserts that check handCount, discardCount, deckCount, and scoring Values vs. Expected Values
    // Remember the gardens card needs to be included and will need to call the Hand/Discard/Deck Generators

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

  printf("----- BUG 06 TEST SET A (Hand == Discard == Deck) -----\n");
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


  /* -- Test 1 ... -- */
  printf("_____ TEST #1B _____\n");

  // Initialize Game
  memset(&state, 0, sizeof(struct gameState));
  initializeGame(num_players, k, seed, &state);

  // Set-up Parameters
  state.handCount[player] = 5;
  state.discardCount[player] = 5;
  state.deckCount[player] = 5;

  // Run the Test
  scoreReturn = ScoreForTestB(&state, player);
  if(scoreReturn)
  {
    // Nothing for now..
  }
  // If there was a fault detected then print out test parameter information (moved to within ScoreForTest())
  //if(scoreReturn) { printf("__ Test #1 - Fault Detected __\n"); }
  //else { printf("__ Test #1 - Valid __\n");}


  return 0;
}

/* -- ScoreForTestA -- */
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
    printf("Test Information:\n");
    printf("\tTotal Cards: %d ; Hand Count: %d ; Discard Count: %d ; Deck Count: %d\n",total_cards,state->handCount[player],state->discardCount[player],state->deckCount[player] );
    printf("\tCalculated Scores: Hand = %d ; Discard = %d ; Deck = %d\n",score_hand, score_discard, score_deck);
    printf("\t"); DisplayHand(state, player, "Player1");
    printf("\t"); DisplayDiscard(state, player, "Player1");
    printf("\t"); DisplayDeck(state, player, "Player1");
  }


  return flagFail;
}



/* -- ScoreForTestB -- */
int ScoreForTestB(struct gameState *state, int player)
{
  // Variables 
  int flagFail = 0, assertReturn;
  int score_hand ,score_discard, score_deck, total_score, scoreForReturn;
  int total_cards = state->handCount[player] + state->discardCount[player] + state->deckCount[player];

 // Set Up Piles (or should I set Default ones?)
  HandGenerator(state, player, state->handCount[player], curse, treasure_map);
  DiscardGenerator(state, player, state->discardCount[player], curse, treasure_map);
  DeckGenerator(state, player, state->deckCount[player], curse, treasure_map);

  // Set Last Cards in Each Pile to a Specific Card for Checking Offsets
  state->hand[player][state->handCount[player]-1] = great_hall;  // +1
  state->discard[player][state->discardCount[player]-1] = duchy; // +3
  state->deck[player][state->deckCount[player]-1] = province;    // +6

  // Count gardens ... need a better way for this ..
  int gardens_hand = HandCardCount(state, player, gardens);
  int gardens_discard = DiscardCardCount(state, player, gardens);
  int gardens_deck = DeckCardCount(state, player, gardens);

  // Calculations for Comparisons
  score_hand = (HandCardCount(state, player, curse)*-1) + (HandCardCount(state, player, estate)*1) + (HandCardCount(state, player, duchy)*3) + (HandCardCount(state, player, province)*6) + (HandCardCount(state, player, great_hall)*1) + (gardens_hand*(total_cards/10));
  score_discard = (DiscardCardCount(state, player, curse)*-1) + (DiscardCardCount(state, player, estate)*1) + (DiscardCardCount(state, player, duchy)*3) + (DiscardCardCount(state, player, province)*6) + (DiscardCardCount(state, player, great_hall)*1) + (gardens_discard*(total_cards/10));
  score_deck = (DeckCardCount(state, player, curse)*-1) + (DeckCardCount(state, player, estate)*1) + (DeckCardCount(state, player, duchy)*3) + (DeckCardCount(state, player, province)*6) + (DeckCardCount(state, player, great_hall)*1) + (gardens_deck*(total_cards/10));

  total_score = score_hand + score_discard + score_deck;

  scoreForReturn = scoreFor(player, state);

  // Return Value Comparison
  assertReturn = AssertTest(scoreForReturn == total_score, "Total Player Score");
  if(assertReturn) { flagFail = 1; printf("\tscoreFor() Calculated: %d vs. Expected: %d\n", scoreForReturn, total_score); }

  if(flagFail)
  {
    printf("Test Information:\n");
    printf("\tTotal Cards: %d ; Hand Count: %d ; Discard Count: %d ; Deck Count: %d\n",total_cards,state->handCount[player],state->discardCount[player],state->deckCount[player] );
    printf("\tCalculated Scores: Hand = %d ; Discard = %d ; Deck = %d\n",score_hand, score_discard, score_deck);
    printf("\t"); DisplayHand(state, player, "Player1");
    printf("\t"); DisplayDiscard(state, player, "Player1");
    printf("\t"); DisplayDeck(state, player, "Player1");
    if(gardens_hand || gardens_discard || gardens_deck)
    {
      printf("\tGardens Detected: Hand = %d ; Discard = %d ; Deck = %d\n", gardens_hand, gardens_discard, gardens_deck);
    }
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


// count of duplicate cards matching specific card.
int HandCardCount2(struct gameState *state, int player, int choice1, int handPos)
{
    int count = 0;
    int i;
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (i != handPos && state->hand[player][i] == state->hand[player][choice1] && i != choice1) 
        {
            count++;
        }
    }

    return count;
}

// Compare that Pile was Shuffled (careful with small sample sizes ...)
int CheckShuffle(struct gameState *state_old, struct gameState *state_new, int player)
{
  int retVal = -1;
  int i;
  // Only compare against the current deck count (since old discard count will be higher after cards are played)
  for(i=0; i<state_new->deckCount[player]; i++)
  {
    if(state_new->deck[player][i] != state_old->discard[player][i])
    {
        retVal = 1;
        break;
    }
  }

    return retVal;
}



