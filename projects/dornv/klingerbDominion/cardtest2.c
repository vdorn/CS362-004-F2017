/* Program Filename: cardtest2.c
 * Author: Barbara Jane Klinger
 * Date: 10/18/2017
 * Description: Unit tests for the Gardens Dominion card.
 * Input: None.
 * Output: This program implements unit testing for the Gardens card implemented
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
#define TESTCARD "gardens"
#define CARDENUM 10
#define HAND_POS 0
#define PLAYERS 2
#define FALSE 0
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

int main(){

	// Declare local variables: 
	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState Game, TestGame;

	// Create instance of a game:
	initializeGame(PLAYERS, cards, SEED, &Game);
	printf("\n***CREATING NEW DOMINION GAME***\n\n");

	// ONLY CONDITION: The gardens card should not be allowed to be used an action and 
	// there should be no changes to the game state if a gardens card is attempted to
	// be played:
	printf("***GARDENS CONDITION: Should not be playable during the action phase***\n"); 
	printf("\nInitial player hand:\n");
	printHand(&Game, THIS_PLAYER);

	// Replace first card in hand with a garden's card and print to display:
	Game.hand[THIS_PLAYER][0] = CARDENUM;
	printf("\n\nReplacing a card in player hand with %s card:\n", TESTCARD);
	printHand(&Game, THIS_PLAYER);

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

	// Test case plays the gardens card:
	result = cardEffect(CARDENUM, FALSE, FALSE, FALSE, TestGame, HAND_POS, &bonus);
	printf("\n\n***TESTING CONDITION***\n\n");
	printf("The test case has played the %s card:\n\n", TESTCARD);

	// Return result of calling cardEffect should be -1 to indicate non action card:
	printf("Return result of playing card: %d; should be -1\n", result);
	assertTrue(result == -1);

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
