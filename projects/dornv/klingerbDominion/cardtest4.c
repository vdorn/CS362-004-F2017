/* Program Filename: cardtest4.c
 * Author: Barbara Jane Klinger
 * Date: 10/18/2017
 * Description: Unit tests for the Smithy Dominion card.
 * Input: None.
 * Output: This program implements unit testing for the Smithy card implemented
 * by the Dominion game.  The results of the testing are printed to the display
 * for closer inspection and examination.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants:
#define TESTCARD "smithy"
#define CARDENUM 13
#define ADD_CARD 3
#define SMI_CARD 1
#define HAND_POS 0
#define PLAYERS 2
#define FALSE 0
#define TRUE 1
#define SEED 10
#define THIS_PLAYER 0
#define THAT_PLAYER 1

// Function prototypes:
void assertTrue(int);
void printSupply(struct gameState *, struct gameState *, int, int);
void printHand(struct gameState *, int);
void printDiscard(struct gameState *, int);
void printDeck(struct gameState *, int);
void unitTestSuite(struct gameState *, struct gameState *);
int handContains(struct gameState *, int, int);
int discardContains(struct gameState *, int, int);
int deckContains(struct gameState *, int, int);

int main(){

	// Declare local variables:
	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState Game, TestGame;

	// Create an instance of a game:
	initializeGame(PLAYERS, cards, SEED, &Game);
	printf("\n*** INITIALIZING SMITHY CARD UNIT TESTS ***\n\n");

	// CONDITION 1: There are at least 3 cards in the player deck:
	printf("*** SMITHY CONDITION 1: There are at least %d cards in the player's deck ***\n",
		ADD_CARD);
	printf("\nInitial player hand:\n");
	printHand(&Game, THIS_PLAYER);

	// Replace first card in player hand with the smithy card:
	Game.hand[THIS_PLAYER][0] = CARDENUM;
	printf("\n\nReplacing card in player hand with %s card:\n", TESTCARD);
	printHand(&Game, THIS_PLAYER);

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 2: There are less than 3 cards in the player deck:
	printf("\n\n*** SMITHY CONDITION 2: There are less than %d cards in the player's deck ***\n",
		ADD_CARD);
	printf("\nRemoving four cards from player's deck and adding to discard:\n");
	Game.discard[THIS_PLAYER][0] = Game.deck[THIS_PLAYER][1];
	Game.discard[THIS_PLAYER][1] = Game.deck[THIS_PLAYER][2];
	Game.discard[THIS_PLAYER][2] = Game.deck[THIS_PLAYER][3];
	Game.discard[THIS_PLAYER][3] = Game.deck[THIS_PLAYER][4];
	Game.discardCount[THIS_PLAYER] = Game.discardCount[THIS_PLAYER] + 4;
	Game.deck[THIS_PLAYER][1] = -1;
	Game.deck[THIS_PLAYER][2] = -1;
	Game.deck[THIS_PLAYER][3] = -1;
	Game.deck[THIS_PLAYER][4] = -1;
	Game.deckCount[THIS_PLAYER] = Game.deckCount[THIS_PLAYER] - 4;

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame); 

	return 0;
} 

void unitTestSuite(struct gameState *Game, struct gameState *TestGame){

	// Declare local variables:
	int result = SEED;
	int bonus = 0;

	// Test case plays the smithy card:
	result = cardEffect(CARDENUM, FALSE, FALSE, FALSE, TestGame, HAND_POS, &bonus);
	printf("\n\n***TESTING CONDITION***\n\n");
	printf("The test case has played the %s card:\n\n", TESTCARD);

	// Return result of calling cardEffect should be 0 to indicate playable action card:
	printf("Return result of playing card: %d; should be 0\n", result);
	assertTrue(!result);

	// Game state: Player hand should have gained 3 cards and lost the smithy (net 2):
	printf("\nNumber of cards in the player hand: %d; should be %d",
		TestGame->handCount[THIS_PLAYER], Game->handCount[THIS_PLAYER] + ADD_CARD - SMI_CARD);
	printf("\nGAME STATE: Player hand should have a net gain of 2 (3 new - smithy) - ");
	assertTrue(TestGame->handCount[THIS_PLAYER] == (Game->handCount[THIS_PLAYER] + ADD_CARD - SMI_CARD));

	// Game state: Player hand should no longer contain smithy card
	printf("\nPlayer hand is:\n");
	printHand(TestGame, THIS_PLAYER);
	printf("\nGAME STATE: Player hand should no longer contain %s card - ", TESTCARD);
	assertTrue(!handContains(TestGame, THIS_PLAYER, CARDENUM));

	// Game state: Player discard should now contain the smithy card
	printf("\nPlayer discard is:\n");
	printDiscard(TestGame, THIS_PLAYER);
	printf("\nGAME STATE: Player discard should now contain %s card - ", TESTCARD);
	assertTrue(discardContains(TestGame, THIS_PLAYER, CARDENUM));

	// Game state: The new hand cards should come from player's deck/discard:
	printf("\nNumber of cards in player deck/discard: %d; should be: %d",
		TestGame->deckCount[THIS_PLAYER] + TestGame->discardCount[THIS_PLAYER],
		Game->deckCount[THIS_PLAYER] + Game->discardCount[THIS_PLAYER] - ADD_CARD + SMI_CARD);
	printf("\nGAME STATE: The player deck/discard should have net loss of 2 (smithy - 3 new) - ");
	assertTrue(TestGame->deckCount[THIS_PLAYER] + TestGame->discardCount[THIS_PLAYER] ==
		Game->deckCount[THIS_PLAYER] + Game->discardCount[THIS_PLAYER] - ADD_CARD + SMI_CARD);

	// Game state: Opponent hand should not have changed:
	printf("\nNumber of cards in the opponent hand: %d; should be: %d", 
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

int deckContains(struct gameState *game, int player, int card){

	// Declare local variables:
	int index;

	// Search through the hand for the specified card:
	for(index = 0; index < game->deckCount[player]; index++){
	
		// If card found; return true:
		if(game->deck[player][index] == card)
			return TRUE; 
	}
	
	return FALSE;
}

int discardContains(struct gameState *game, int player, int card){

	// Declare local variables:
	int index;

	// Search through the hand for the specified card:
	for(index = 0; index < game->discardCount[player]; index++){
	
		// If card found; return true:
		if(game->discard[player][index] == card)
			return TRUE; 
	}
	
	return FALSE;
}

int handContains(struct gameState *game, int player, int card){

	// Declare local variables:
	int index;

	// Search through the hand for the specified card:
	for(index = 0; index < game->handCount[player]; index++){
	
		// If card found; return true:
		if(game->hand[player][index] == card)
			return TRUE; 
	}
	
	return FALSE;
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
