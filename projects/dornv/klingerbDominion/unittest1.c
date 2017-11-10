/* Program Filename: unittest1.c
 * Author: Barbara Jane Klinger
 * Date: 10/18/2017
 * Description: Unit tests for the fullDeckCount Dominion function.
 * Input: None.
 * Output: This program implements unit testing for the fullDeckCount function
 * implemented by the Dominion game.  The results of the testing are printed
 * to the display for closer inspection and examination.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants:
#define TESTFUN "fullDeckCount"
#define TESTCARD "minion"
#define TESTENUM 17
#define GOLDENUM 6
#define STEWENUM 18
#define ESTENUM 1
#define NUMTEST 10
#define PLAYERS 2
#define FALSE 0
#define TRUE 1
#define SEED 10
#define VOID -1
#define THIS_PLAYER 0

// Function prototypes:
void assertTrue(int);
void printSupply(struct gameState *, struct gameState *, int, int);
void printHand(struct gameState *, int);
void printDiscard(struct gameState *, int);
void printDeck(struct gameState *, int);
void unitTestSuite(struct gameState *, struct gameState *);
int handCount(struct gameState *, int, int);
int discardCount(struct gameState *, int, int);
int deckCount(struct gameState *, int, int);
void setDeck(struct gameState *, int, int);
void setHand(struct gameState *, int, int);
void setDiscard(struct gameState *, int, int);

int main(){

	// Declare local variables:
	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState Game, TestGame;

	// Create instance of a game:
	initializeGame(PLAYERS, cards, SEED, &Game);
	printf("\n*** INITIALIZING %s FUNCTION UNIT TESTS ***\n\n", TESTFUN);

	// CONDITION 1: Hand/Deck/Discard empty
	printf("*** %s FUNCTION CONDITION 1: Hand/Deck/Discard all empty ***", TESTFUN);
	setDeck(&Game, VOID, NUMTEST);
	Game.deckCount[THIS_PLAYER] = FALSE;
	setHand(&Game, VOID, NUMTEST);
	Game.handCount[THIS_PLAYER] = FALSE;
	setDiscard(&Game, VOID, NUMTEST);
	Game.discardCount[THIS_PLAYER] = FALSE;

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 2: Hand/Deck/Discard sets do not contain specified card:
	printf("\n*** %s FUNCTION CONDITION 2: Hand/Deck/Discard do not contain search card ***", TESTFUN);
	setDeck(&Game, GOLDENUM, NUMTEST);
	Game.deckCount[THIS_PLAYER] = NUMTEST;
	setHand(&Game, STEWENUM, NUMTEST);
	Game.handCount[THIS_PLAYER] = NUMTEST;
	setDiscard(&Game, ESTENUM, NUMTEST);
	Game.discardCount[THIS_PLAYER] = NUMTEST;

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 3: Hand/Deck/Discard sets do contain specified card:
	printf("\n*** %s FUNCTION CONDITION 3: Hand/Deck/Discard contain search card ***", TESTFUN);
	Game.deck[THIS_PLAYER][3] = TESTENUM;
	Game.deck[THIS_PLAYER][6] = TESTENUM;
	Game.discard[THIS_PLAYER][0] = TESTENUM;
	Game.hand[THIS_PLAYER][9] = TESTENUM;

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	return 0;
}

void unitTestSuite(struct gameState *Game, struct gameState *TestGame){

	// Declare local variables:
	int testCount = VOID;
	int actualCount = VOID;

	// Run the fullDeckCount function to search for the test card:
	testCount = fullDeckCount(THIS_PLAYER, TESTENUM, TestGame);
	actualCount = deckCount(Game, THIS_PLAYER, TESTENUM) +
		discardCount(Game, THIS_PLAYER, TESTENUM) +
		handCount(Game, THIS_PLAYER, TESTENUM);
	printf("\n\n*** TESTING CONDITION ***\n\n");
	printf("Counting the number of %s cards in full deck:\n\n", TESTCARD);

	// Game state: function should return the correct number of cards:
	printf("Number of %s cards: %d; should be: %d",
		TESTCARD, testCount, actualCount);
	printf("\nGAME STATE: function should have returned the correct number of cards - ");
	assertTrue(testCount == actualCount);

	// Game state: Player hand should not have changed:
	printf("\nNumber of cards in the player hand: %d; should be: %d", 
		TestGame->handCount[THIS_PLAYER], Game->handCount[THIS_PLAYER]);
	printf("\nGAME STATE: No changes to the player hand - ");
	assertTrue(TestGame->handCount[THIS_PLAYER] == Game->handCount[THIS_PLAYER]);
	printf("\nPlayer hand is:\n");
	printHand(TestGame, THIS_PLAYER);
	printf("\nPlayer hand should be:\n");
	printHand(Game, THIS_PLAYER);

	// Game state: Player deck should not have changed:
	printf("\n\nNumber of cards in the player deck: %d; should be: %d", 
		TestGame->deckCount[THIS_PLAYER], Game->deckCount[THIS_PLAYER]);
	printf("\nGAME STATE: No changes to the player deck - ");
	assertTrue(TestGame->deckCount[THIS_PLAYER] == Game->deckCount[THIS_PLAYER]);
	printf("\nPlayer deck is:\n");
	printDeck(TestGame, THIS_PLAYER);
	printf("\nPlayer deck should be:\n");
	printDeck(Game, THIS_PLAYER);

	// Game state: Player discard should not have changed:
	printf("\n\nNumber of cards in the player discard: %d; should be: %d", 
		TestGame->discardCount[THIS_PLAYER], Game->discardCount[THIS_PLAYER]);
	printf("\nGAME STATE: No changes to the player discard - ");
	assertTrue(TestGame->discardCount[THIS_PLAYER] == Game->discardCount[THIS_PLAYER]);
	printf("\nPlayer discard is:\n");
	printDiscard(TestGame, THIS_PLAYER);
	printf("\nPlayer discard should be:\n");
	printDiscard(Game, THIS_PLAYER);
	printf("\n");
}

void setDeck(struct gameState *game, int card, int num){

	// Declare local variables:
	int index;

	// Add the specified cards to the deck:
	for(index = 0; index < num; index++){

		game->deck[THIS_PLAYER][index] = card;
	}
}

void setHand(struct gameState *game, int card, int num){

	// Declare local variables:
	int index;

	// Add the specified cards to the deck:
	for(index = 0; index < num; index++){

		game->hand[THIS_PLAYER][index] = card;
	}
}

void setDiscard(struct gameState *game, int card, int num){

	// Declare local variables:
	int index;

	// Add the specified cards to the deck:
	for(index = 0; index < num; index++){

		game->discard[THIS_PLAYER][index] = card;
	}
}



int deckCount(struct gameState *game, int player, int card){

	// Declare local variables:
	int count = 0;
	int index;

	// Search through the hand for the specified card:
	for(index = 0; index < game->deckCount[player]; index++){
	
		// If card found; increment count:
		if(game->deck[player][index] == card)
			count++; 
	}
	
	return count;
}

int discardCount(struct gameState *game, int player, int card){

	// Declare local variables:
	int count = 0;
	int index;

	// Search through the hand for the specified card:
	for(index = 0; index < game->discardCount[player]; index++){
	
		// If card found; increment count:
		if(game->discard[player][index] == card)
			count++; 
	}
	
	return count;
}

int handCount(struct gameState *game, int player, int card){

	// Declare local variables:
	int count = 0;
	int index;

	// Search through the hand for the specified card:
	for(index = 0; index < game->handCount[player]; index++){
	
		// If card found; increment count:
		if(game->hand[player][index] == card)
			count++; 
	}
	
	return count;
}

void assertTrue(int result){

	// Print assert statement according to passed results:
	if (result == FALSE)
		printf("TEST FAILED!!\n");
	else
		printf("TEST PASSED!!\n");
}

void printSupply(struct gameState *expected, struct gameState *test, int start, int end){

	// Declare local variables:
	int index;
	
	// Print result headers:
	printf("\nCard:\tIs:\tShould be:\tTest:\n");

	// Loop through specified supply counts to compare expected and test values:
	for(index = start; index < end; index++){

		// Print results to the display:
		printf("%d\t%d\t%d\t\t", index, test->supplyCount[index], expected->supplyCount[index]);
		assertTrue(test->supplyCount[index] == expected->supplyCount[index]);
	 }
}

void printHand(struct gameState *game, int player){

	// Declare local variables:
	int index;

	// Determine if any cards are present in the hand:
	if(game->handCount[player] > 0){

		// Print the enum values of the cards in the hand:
		for(index = 0; index < game->handCount[player]; index++){
	 						
			printf("%d, ", game->hand[player][index]);
		}
	}
	else{
		printf("Empty Set");
	}
}

void printDeck(struct gameState *game, int player){

	// Declare local variables:
	int index;
	
	// Determine if any cards are present in the deck:
	if(game->deckCount[player] > 0){
		
		// Print the enum values of the cards in the deck:
		for(index = 0; index < game->deckCount[player]; index++){

			printf("%d, ", game->deck[player][index]);
		}
	}
	else{
		printf("Empty Set");
	}
}

void printDiscard(struct gameState *game, int player){

	// Declare local variables: 
	int index;
	
	// Determine if any cards are present in the discard pile:
	if(game->discardCount[player] > 0){
			
		// Print enum values of the discard pile cards:
		for(index = 0; index < game->discardCount[player]; index++){

			printf("%d, ", game->discard[player][index]);
		}
	}
	else{ 
		printf("Empty Set"); 
	}
}


