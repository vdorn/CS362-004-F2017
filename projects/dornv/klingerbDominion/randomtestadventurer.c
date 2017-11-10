/* Program Filename: randomtestadventurer.c
 * Author: Barbara Jane Klinger
 * Date: 11/03/2017
 * Description: Automated random test generator for the Adventurer
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
#define TESTCARD "adventurer"
#define CARDENUM 7
#define TESTNUM 100000
#define MIN_PLAYERS 2
#define MAX_CARD_ENUM 26
#define MIN_CARD_ENUM 0

// Declare struct:
struct statusFlags{

	int coinHandAdd;
	int adHandSub;
	int coinDeckSub;
	int adDiscAdd;
	int trashSame;
	int oppHandSame;
	int oppDeckSame;
	int oppDiscSame;
	int pilesSame;
};

// Function prototypes:
int assertTrue(int);
void compareGameStates(struct gameState *, struct gameState *, struct statusFlags *, int);
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

		// Copy game instance to test case:
		memcpy(&TestGame, &Game, sizeof(struct gameState));

		// Test case plays the card under test:
		cardEffect(CARDENUM, FALSE, FALSE, FALSE, &TestGame, handPos, &bonus);
		
		// Initialize status flags and compare actual and expected game state conditions:
		initializeFlags(&State);
		compareGameStates(&Game, &TestGame, &State, player);

		// Record statistic:
		printFail = recordStats(&State, &Total);
		
		// If a test failed, print out the stats of the failed test:
		if(printFail){

			printf("\nTEST CASE FAILED!!: Total players: %d; player number: %d; hand position: %d; ", 
				playerNumber, player, handPos);
			printf("Hand: %d; Deck: %d; Discard: %d\n", Game.handCount[player],
				Game.deckCount[player], Game.discardCount[player]);
			printf("Flags: CH+: %d; AH-: %d; CD-: %d; AD+: %d; ", State.coinHandAdd, 
				State.adHandSub, State.coinDeckSub, State.adDiscAdd);
			printf("T=: %d, OH=: %d; ODe=: %d; ODi=: %d: ", State.trashSame, 
				State.oppHandSame, State.oppDeckSame, State.oppDiscSame);
			printf("P=: %d\n", State.pilesSame); 
		}
	}

	// Print overall random test statistics:
	printf("\n*** %s card total tests: %d\n", TESTCARD, 
		TESTNUM); 
	printf("*** Condition Statistics:\n");
	printf("Player hand gains treasure cards(CH+): %d failed tests\n", Total.coinHandAdd);
	printf("Player hand removes adventurer card(AH-): %d failed tests\n", Total.adHandSub);
	printf("Treasure cards taken from player deck(CD-): %d failed tests\n", Total.coinDeckSub);
	printf("Adventurer card added to discard(AD+): %d failed tests\n", Total.adDiscAdd);
	printf("No cards are trashed(T=): %d failed tests\n", Total.trashSame);
	printf("No opponent hand cards changed(OH=): %d failed tests\n", Total.oppHandSame);
	printf("No opponent deck cards changed(ODe=): %d failed tests\n", Total.oppDeckSame);
	printf("No opponent discard cards changed(ODi=): %d failed tests\n", Total.oppDiscSame);
	printf("No kingdom or victory card piles changed(P=): %d failed tests\n\n", Total.pilesSame);
		
	return 0;
}

void compareGameStates(struct gameState *Game, struct gameState *TestGame, 
	struct statusFlags *State, int player){

	// Declare local variables:
	int actualNumber, expectedNumber, index;

	// Player hand gains two treasure cards:
	actualNumber = handContains(TestGame, player, copper) 
		+ handContains(TestGame, player, silver)
		+ handContains(TestGame, player, gold);
	expectedNumber = handContains(Game, player, copper) 
		+ handContains(Game, player, silver) +
		+ handContains(Game, player, gold) + 2;
	
	if(actualNumber != expectedNumber){

		// If treasure cards not added to hand, check to see if there are
		// any in the deck or discard that should have been added:
		actualNumber = deckContains(TestGame, player, copper)
			+ deckContains(TestGame, player, silver) 
			+ deckContains(TestGame, player, gold)
			+ discardContains(TestGame, player, copper)
			+ discardContains(TestGame, player, silver)
			+ discardContains(TestGame, player, gold);
		State->coinHandAdd = assertTrue(actualNumber == 0);
	}

	// Player hand removes adventurer card:
	actualNumber = handContains(TestGame, player, adventurer);
	expectedNumber = handContains(Game, player, adventurer) - 1;
	State->adHandSub = assertTrue(actualNumber == expectedNumber); 
	
	// Treasure cards removed from player's deck (and discard if shuffle):
	actualNumber = deckContains(TestGame, player, copper)
		+ deckContains(TestGame, player, silver) 
		+ deckContains(TestGame, player, gold)
		+ discardContains(TestGame, player, copper)
		+ discardContains(TestGame, player, silver)
		+ discardContains(TestGame, player, gold);
	expectedNumber = deckContains(Game, player, copper)
		+ deckContains(Game, player, silver) 
		+ deckContains(Game, player, gold)
		+ discardContains(Game, player, copper)
		+ discardContains(Game, player, silver)
		+ discardContains(Game, player, gold) - 2;

	State->coinDeckSub = assertTrue(actualNumber == expectedNumber);		
	
	// Adventurer card is added to discard pile:
	actualNumber = deckContains(TestGame, player, adventurer) 
		+ discardContains(TestGame, player, adventurer);
	expectedNumber = deckContains(Game, player, adventurer)
		+ discardContains(TestGame, player, adventurer) + 1;
	State->adDiscAdd = assertTrue(actualNumber == expectedNumber);
	
	// No cards trashed by either player:
	actualNumber = TestGame->playedCardCount;
	expectedNumber = Game->playedCardCount;
	State->trashSame = assertTrue(actualNumber == expectedNumber);
	
	// No changes to other player's hand/deck/discard piles
	for(index = 0; index < Game->numPlayers; index++){
	
		if(index != player){
			// Compare actual and expected hand values:
			State->oppHandSame = assertTrue(TestGame->handCount[index] == Game->handCount[index]);

			// Compare actual and expected deck values:
			State->oppDeckSame = assertTrue(TestGame->deckCount[index] == Game->deckCount[index]);
		
			// Compare acutal and expected discard values:
			State->oppDiscSame = assertTrue(TestGame->discardCount[index] 
				== Game->discardCount[index]);
		}
	} 
	
	// No changes to kingdom or victory piles:
	for(index = 0; index < treasure_map + 1; index++){

		State->pilesSame = assertTrue(TestGame->supplyCount[index] = Game->supplyCount[index]);
	}
	
}

int recordStats(struct statusFlags *State, struct statusFlags *Total){

	// Declare local variables:
	int testFailed = FALSE;
	
	// Record statistics:
	if(State->coinHandAdd == FALSE){
		Total->coinHandAdd++;
		testFailed = TRUE;
	}
	if(State->adHandSub == FALSE){
		Total->adHandSub++;
		testFailed = TRUE;
	}
	if(State->coinDeckSub == FALSE){
		Total->coinDeckSub++;
		testFailed = TRUE;
	}
	if(State->adDiscAdd == FALSE){
		Total->adDiscAdd++;
		testFailed = TRUE;
	}
	if(State->trashSame == FALSE){
		Total->trashSame++;
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
	if(State->pilesSame == FALSE){
		Total->pilesSame++;
		testFailed = TRUE;
	}
	
	return testFailed;
}

void initializeFlags(struct statusFlags *State){

	State->coinHandAdd = TRUE;
	State->adHandSub= TRUE;
	State->coinDeckSub = TRUE;
	State->adDiscAdd = TRUE;
	State->trashSame = TRUE;
	State->oppHandSame = TRUE;
	State->oppDeckSame = TRUE;
	State->oppDiscSame = TRUE;
	State->pilesSame = TRUE;
}

void initializeCounters(struct statusFlags *State){

	State->coinHandAdd = 0;
	State->adHandSub= 0;
	State->coinDeckSub = 0;
	State->adDiscAdd = 0;
	State->trashSame = 0;
	State->oppHandSame = 0;
	State->oppDeckSame = 0;
	State->oppDiscSame = 0;
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
