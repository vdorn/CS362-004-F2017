/* Program Filename: randomtestcard1.c
 * Author: Barbara Jane Klinger
 * Date: 11/03/2017
 * Description: Automated random test generator for the Smithy
 * 	Dominion Card.  Random test cases are created, which then
 * 	play the action card under test.  The actual game state
 * 	values are then compared with the expected values and
 * 	statistics are recorded for closer examination. A test case
 * 	only needs to fail one condition test to be considered
 * 	a failed test case.
 * Input: None.
 * Output: The random values and game state condition flags for
 * 	failed test cases are printed to display; test cases
 * 	that pass are not.  After the specified number of tests
 * 	are run, the number of tests that failed each game state
 * 	condition are printed to display.   
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants:
#define FALSE 0
#define TRUE 1
#define TESTCARD "smithy"
#define CARDENUM 13
#define NEWCARD 3
#define TESTNUM 100000
#define MIN_PLAYERS 2
#define MAX_CARD_ENUM 26
#define MIN_CARD_ENUM 0

// Declare struct:
struct statusFlags{

	int newHandAdd;
	int smiHandSub;
	int smiDiscAdd;
	int newDeckSub;
	int oppHandSame;
	int oppDeckSame;
	int oppDiscSame;
	int trashSame;
	int pilesSame;
};

// Function prototypes:
int assertTrue(int);
void compareGameStates(struct gameState *, struct gameState *, struct statusFlags *, int, int);
int handContains(struct gameState *, int, int);
int deckContains(struct gameState *, int, int);
int discardContains(struct gameState *, int, int);
void initializeFlags(struct statusFlags *);
void initializeCounters(struct statusFlags *);
int recordStats(struct statusFlags *, struct statusFlags *);

int main(){

	// Declare local variables:
	int index, randomIndex, playerNumber, player, handPos;
	int printFail = FALSE;
	int bonus = 0;
	struct gameState Game, TestGame;
	struct statusFlags State, Total;
	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy};

	// Initialize flag counters:
	initializeCounters(&Total);

	// Print test information:
	printf("\n*** RANDOM TESTER: %s card ***\n", TESTCARD);

	// Generate random "sane" values to populate the gameState struct and test the
	// randomly generated instance:
	for(index = 0; index < TESTNUM; index++){

		// Random number of players:
		playerNumber = rand() % (MAX_PLAYERS + 1 - MIN_PLAYERS) + MIN_PLAYERS;
		
		// Generate psuedo-random instance of game:
		initializeGame(playerNumber, cards, rand(), &Game);

		// Radomly choose a player: 
		player = rand() % playerNumber;
		Game.whoseTurn = player;

		// Randomly create that player's deck:
		Game.deckCount[player] = rand() % (MAX_DECK + 1);
		for(randomIndex = 0; randomIndex < Game.deckCount[player]; randomIndex++){

			Game.deck[player][randomIndex] = 
				rand() % (MAX_CARD_ENUM + 1 - MIN_CARD_ENUM) + MIN_CARD_ENUM;
		}

		// Randomly create that player's hand:
		Game.handCount[player] = rand() % (MAX_HAND + 1);
		for(randomIndex = 0; randomIndex < Game.handCount[player]; randomIndex++){

			Game.hand[player][randomIndex] =
				rand() % (MAX_CARD_ENUM + 1 - MIN_CARD_ENUM) + MIN_CARD_ENUM;
		}

		// Randomly create that player's discard:
		Game.discardCount[player] = rand() % (MAX_HAND + MAX_DECK + 1);
		for(randomIndex = 0; randomIndex < Game.discardCount[player]; randomIndex++){

			Game.discard[player][randomIndex] = 
				rand() % (MAX_CARD_ENUM + 1 - MIN_CARD_ENUM) + MIN_CARD_ENUM;
		} 

		// Randomly insert card under test into hand:
		if(Game.handCount[player] != 0){
			handPos = rand() % Game.handCount[player];
		}
		else{
			Game.handCount[player] = 1;
			handPos = 0;
		}

		Game.hand[player][handPos] = CARDENUM;

		// Copy game instancce to test case:
		memcpy(&TestGame, &Game, sizeof(struct gameState));

		// Test case plays the card under test:
		cardEffect(CARDENUM, FALSE, FALSE, FALSE, &TestGame, handPos, &bonus);

		// Initialize status flags and compare actual and expected game state conditions:
		initializeFlags(&State);
		compareGameStates(&Game, &TestGame, &State, player, handPos);

		// Record statistic:
		printFail = recordStats(&State, &Total);
		
		// If a test failed, print out the stats of the failed test:
		if(printFail){

			printf("\nTEST CASE FAILED!!: Total players: %d; player num: %d; hand pos: %d; ", 
				playerNumber, player, handPos);
			printf("Hand: %d; Deck: %d; Discard: %d\n", Game.handCount[player], 
				Game.deckCount[player], Game.discardCount[player]);
			printf("Flags: NH+: %d; SH-: %d; SDi+: %d; NDe-: %d; ", State.newHandAdd, 
				State.smiHandSub, State.smiDiscAdd, State.newDeckSub);
			printf("OH=: %d, ODe=: %d; ODi=: %d; T=: %d; P=: %d;\n", State.oppHandSame, 
				State.oppDeckSame, State.oppDiscSame, State.trashSame, State.pilesSame);
		}
	}

	// Print overall random test statistics:
	printf("\n*** %s card total tests: %d\n", TESTCARD, 
		TESTNUM); 
	printf("*** Condition Statistics:\n");
	printf("Three new cards added to player hand(NH+): %d failed tests\n", Total.newHandAdd);
	printf("Smithy removed from player hand(SH-): %d failed tests\n", Total.smiHandSub);
	printf("Smithy added to player discard(SDi+): %d failed tests\n", Total.smiDiscAdd);
	printf("Three cards removed from player deck(NDe-): %d failed tests\n", Total.newDeckSub);
	printf("No changes to opponents hand(OH=): %d failed tests\n", Total.oppHandSame);
	printf("No changes to opponents deck(ODe=): %d failed tests\n", Total.oppDeckSame);
	printf("No changes to oppponents discard(ODi=): %d failed tests\n", Total.oppDiscSame);
	printf("No cards are trashed(T=): %d failed tests\n", Total.trashSame);
	printf("No kingdom or victory card piles changed(P=): %d failed tests\n\n", Total.pilesSame);
		
	return 0;
}

void compareGameStates(struct gameState *Game, struct gameState *TestGame, 
	struct statusFlags *State, int player, int handPos){

	// Declare local variables:
	int actualNumber, expectedNumber, index;

	// Execute loop to determine opponent game state conditions:
	for(index = 0; index < Game->numPlayers; index++){

		if(index != player){
		
			// No changes to opponent hands:
			actualNumber = TestGame->handCount[index];
			expectedNumber = Game->handCount[index];
			State->oppHandSame = assertTrue(actualNumber == expectedNumber);

			// No changes to opponent decks:
			actualNumber = TestGame->deckCount[index];
			expectedNumber = Game->deckCount[index];
			State->oppDeckSame = assertTrue(actualNumber == expectedNumber);

			// There should be no changes to the opponent discard:
			actualNumber = TestGame->discardCount[index];
			expectedNumber = Game->discardCount[index];
			State->oppDiscSame = assertTrue(actualNumber == expectedNumber);
		}
	}

	// Player hand removes smithy card:
	actualNumber = TestGame->hand[player][handPos];
	expectedNumber = Game->hand[player][handPos];
	State->smiHandSub = assertTrue(actualNumber != expectedNumber);

	// Player hand gains three new cards for a net gain 
	// of two (supposed to lose smithy card)
	actualNumber = handContains(TestGame, player, CARDENUM);
	expectedNumber = handContains(Game, player, CARDENUM) + NEWCARD - 1;
	State->newHandAdd = assertTrue(actualNumber == expectedNumber); 		
	
	// Player deck (and/or discard with shuffle) removes three cards:
	// For a net loss of two(supposed to gain Smithy card):
	actualNumber = TestGame->discardCount[player] + TestGame->deckCount[player];
	expectedNumber = Game->discardCount[player] + Game->deckCount[player] - NEWCARD + 1;
	State->newDeckSub = assertTrue(actualNumber == expectedNumber);

	// Smithy card is added to discard pile:
	actualNumber = discardContains(TestGame, player, CARDENUM) 
		+ deckContains(TestGame, player, CARDENUM);
	expectedNumber = discardContains(Game, player, CARDENUM) 
		+ deckContains(Game, player, CARDENUM) + 1;
	State->smiDiscAdd = assertTrue(actualNumber == expectedNumber);
	
	// No cards trashed by any player:
	actualNumber = TestGame->playedCardCount;
	expectedNumber = Game->playedCardCount;
	State->trashSame = assertTrue(actualNumber == expectedNumber);
	
	// No changes to other kingdom or victory piles:
	for(index = 0; index < treasure_map + 1; index++){

		State->pilesSame = assertTrue(TestGame->supplyCount[index] 
			== Game->supplyCount[index]);
	}
}

int recordStats(struct statusFlags *State, struct statusFlags *Total){

	// Declare local variables:
	int testFailed = FALSE;

	// Record statistics:
	if(State->newHandAdd == FALSE){
		Total->newHandAdd++;
		testFailed = TRUE;
	}
	if(State->smiHandSub == FALSE){
		Total->smiHandSub++;
		testFailed = TRUE;
	}
	if(State->smiDiscAdd == FALSE){
		Total->smiDiscAdd++;
		testFailed = TRUE;
	}
	if(State->newDeckSub == FALSE){
		Total->newDeckSub++;
		testFailed = TRUE;
	}
	if(State->oppHandSame == FALSE){
		Total->oppHandSame++;
		testFailed = TRUE;
	}
	if(State->oppDeckSame == FALSE){
		Total->oppDeckSame++;
		testFailed = TRUE;
	}
	if(State->oppDiscSame == FALSE){
		Total->oppDiscSame++;
		testFailed = TRUE;
	}
	if(State->trashSame == FALSE){
		Total->trashSame++;
		testFailed = TRUE;
	}
	if(State->pilesSame == FALSE){
		Total->pilesSame++;
		testFailed = TRUE;
	}
	
	return testFailed;
}

void initializeFlags(struct statusFlags *State){

	State->newHandAdd = TRUE;
	State->smiHandSub = TRUE;
	State->smiDiscAdd = TRUE;
	State->newDeckSub = TRUE;
	State->oppHandSame = TRUE;
	State->oppDeckSame = TRUE;
	State->oppDiscSame = TRUE;
	State->trashSame = TRUE;
	State->pilesSame = TRUE;
}

void initializeCounters(struct statusFlags *State){

	State->newHandAdd = 0;
	State->smiHandSub = 0;
	State->smiDiscAdd = 0;
	State->newDeckSub = 0;
	State->oppHandSame = 0;
	State->oppDeckSame = 0;
	State->oppDiscSame = 0;
	State->trashSame = 0;
	State->pilesSame = 0;
}

int discardContains(struct gameState *game, int player, int card){

	// Declare local variables:
	int index;
	int counter = 0;

	// Search through the hand and count any instances of the specified card:
	for(index = 0; index < game->discardCount[player]; index++){

		if(game->discard[player][index] == card)
			counter++;
	}

	return counter;
}


int deckContains(struct gameState *game, int player, int card){

	// Declare local variables:
	int index;
	int counter = 0;

	// Search through the hand and count any instances of the specified card:
	for(index = 0; index < game->deckCount[player]; index++){

		if(game->deck[player][index] == card)
			counter++;
	}

	return counter;
}

int handContains(struct gameState *game, int player, int card){

	// Declare local variables:
	int index;
	int counter = 0;

	// Search through the hand and count any instances of the specified card:
	for(index = 0; index < game->handCount[player]; index++){

		if(game->hand[player][index] == card)
			counter++;
	}

	return counter;
}

int assertTrue(int result){

	// Determine assert result and return boolean representation:
	if(result == FALSE){
		return FALSE;
	}
	else{
		return TRUE;
	}
}
