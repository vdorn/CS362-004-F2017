/* Program Filename: unittest3.c
 * Author: Barbara Jane Klinger
 * Date: 10/18/2017
 * Description: Unit tests for the shuffle Dominion function.
 * Input: None.
 * Output: This program implements unit testing for the shuffle function
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
#define TESTFUN "shuffle"
#define SEA_CARD "sea_hag"
#define SEA_ENUM 25
#define NUM_TEST 5
#define PLAYERS 2
#define FALSE 0
#define TRUE 1
#define SEED 10
#define VOID -1
#define THIS_PLAYER 0
#define THAT_PLAYER 1

// Function prototypes:
void assertTrue(int);
void printSupply(struct gameState *, struct gameState *, int, int);
void printHand(struct gameState *, int);
void printDiscard(struct gameState *, int);
void printDeck(struct gameState *, int);
void unitTestSuite(struct gameState *, struct gameState *);
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

	// CONDITION 1: Both deck and discard contain cards:
	printf("*** %s FUNCTION CONDITION 1: Deck and Discard both contain cards ***\n\n", TESTFUN);
	setDiscard(&Game, SEA_ENUM, NUM_TEST);
	Game.discardCount[THIS_PLAYER] = NUM_TEST;

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 2: Deck contains no cards and discard contain cards:
	printf("\n\n*** %s FUNCTION CONDITION 2: Deck contains no cards and Discard contain cards ***\n\n", TESTFUN);
	setDeck(&Game, VOID, NUM_TEST);
	Game.deckCount[THIS_PLAYER] = FALSE;

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 3: Deck contains cards and discard contains no cards:
	printf("\n\n*** %s FUNCTION CONDITION 3: Deck contains cards and Discard contains no cards ***\n\n", TESTFUN);
	setDeck(&Game, SEA_ENUM, NUM_TEST);
	Game.deckCount[THIS_PLAYER] = NUM_TEST;
	setDiscard(&Game, VOID, NUM_TEST);
	Game.discardCount[THIS_PLAYER] = FALSE;

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);


	return 0;
}

void unitTestSuite(struct gameState *Game, struct gameState *TestGame){

	// Declare local variables:
	int result = SEED;

	// Print initial player deck and discard:
	printf("Initial player deck:\n");
	printDeck(Game, THIS_PLAYER);
	printf("\nInitial player discard:\n");
	printDiscard(Game, THIS_PLAYER);

	// Call the shuffle function to shuffle the player's deck and discard:
	result = shuffle(THIS_PLAYER, TestGame);
	printf("\n\n*** TESTING CONDITION ***\n\n");
	printf("Shuffling deck and discard cards together:\n\n");
	
	// Return result should be 0 indicating a successful shuffle:
	printf("Return result of calling function: %d; should be: 0\n", result);
	assertTrue(result == 0);

	// Game state: The deck and discard cards should be shuffled and be present in player's deck:
	printf("\nShuffled player deck:\n");
	printDeck(TestGame, THIS_PLAYER);
	printf("\nNumber of cards in player deck: %d; should be: %d", 
		TestGame->deckCount[THIS_PLAYER], Game->deckCount[THIS_PLAYER] + NUM_TEST);
	printf("\nGAME STATE: Player deck should now contain cards from discard - ");
	assertTrue(TestGame->deckCount[THIS_PLAYER] == Game->deckCount[THIS_PLAYER] + NUM_TEST); 

	// Game state: Player discard should be empty:
	printf("\nShuffled player discard:\n");
	printDiscard(Game, THIS_PLAYER);
	printf("\nNumber of cards in player discard: %d; should be: %d",
		TestGame->discardCount[THIS_PLAYER], Game->discardCount[THIS_PLAYER] - NUM_TEST);
	printf("\nGAME STATE: Player discard should be empty - ");
	assertTrue(TestGame->discardCount[THIS_PLAYER] == Game->discardCount[THIS_PLAYER] - NUM_TEST);

	// Game state: Player hand should not have changed:
	printf("\nNumber of cards in the player hand: %d; should be: %d", 
		TestGame->handCount[THIS_PLAYER], Game->handCount[THIS_PLAYER]);
	printf("\nGAME STATE: No changes to the player hand - ");
	assertTrue(TestGame->handCount[THIS_PLAYER] == Game->handCount[THIS_PLAYER]);
	printf("\nPlayer hand is:\n");
	printHand(TestGame, THIS_PLAYER);
	printf("\nPlayer hand should be:\n");
	printHand(Game, THIS_PLAYER);

	// Game state: Opponent hand should not have changed:
	printf("\n\nNumber of cards in the opponent hand: %d; should be: %d", 
		TestGame->handCount[THAT_PLAYER], Game->handCount[THAT_PLAYER]);
	printf("\nGAME STATE: No changes to the opponent hand - ");
	assertTrue(TestGame->handCount[THAT_PLAYER] == Game->handCount[THAT_PLAYER]);
	printf("\nOpponent hand is:\n");
	printHand(TestGame, THAT_PLAYER);
	printf("\nOpponent hand should be:\n");
	printHand(Game, THAT_PLAYER);

	// Game state: Opponent deck should not have changed:
	printf("\n\nNumber of cards in the opponent deck: %d; should be: %d", 
		TestGame->deckCount[THAT_PLAYER], Game->deckCount[THAT_PLAYER]);
	printf("\nGAME STATE: No changes to the opponent deck - ");
	assertTrue(TestGame->deckCount[THAT_PLAYER] == Game->deckCount[THAT_PLAYER]);
	printf("\nOpponent deck is:\n");
	printDeck(TestGame, THAT_PLAYER);
	printf("\nOpponent deck should be:\n");
	printDeck(Game, THAT_PLAYER);

	// Game state: Opponent discard should not have changed:
	printf("\n\nNumber of cards in the opponent discard: %d; should be: %d", 
		TestGame->discardCount[THAT_PLAYER], Game->discardCount[THAT_PLAYER]);
	printf("\nGAME STATE: No changes to the opponent discard - ");
	assertTrue(TestGame->discardCount[THAT_PLAYER] == Game->discardCount[THAT_PLAYER]);
	printf("\nOpponent discard is:\n");
	printDiscard(TestGame, THAT_PLAYER);
	printf("\nOpponent discard should be:\n");
	printDiscard(Game, THAT_PLAYER);

	// Game state: No changes to victory card piles:
	printf("\n\nGAME STATE: No changes to Victory cards:");
	printSupply(Game, TestGame, curse, copper);

	// Game state: No changes to treasure card piles:
	printf("\n\nGAME STATE: No changes to treasure cards:");
	printSupply(Game, TestGame, copper, adventurer);

	// Game state: No changes to kingdom card piles:
	printf("\n\nGAME STATE: No changes to kingdom cards:");
	printSupply(Game, TestGame, adventurer, treasure_map + 1);
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

