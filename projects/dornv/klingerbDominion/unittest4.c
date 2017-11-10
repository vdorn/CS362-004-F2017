/* Program Filename: unittest4.c
 * Author: Barbara Jane Klinger
 * Date: 10/18/2017
 * Description: Unit tests for the gainCard Dominion function.
 * Input: None.
 * Output: This program implements unit testing for the gainCard function
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
#define TESTFUN "gainCard"
#define CUR_CARD "curse"
#define CUR_ENUM 0
#define SMI_CARD "smithy"
#define SMI_ENUM 13
#define REM_CARD "remodel"
#define REM_ENUM 12
#define ADD_CARD 1
#define PLAYERS 2
#define FALSE 0
#define TRUE 1
#define SEED 10
#define VOID -1
#define SUCCESS 0
#define THIS_PLAYER 0
#define THAT_PLAYER 1
#define DISC_FLAG 0
#define DECK_FLAG 1
#define HAND_FLAG 2

// Function prototypes:
void assertTrue(int);
void printSupply(struct gameState *, struct gameState *, int, int);
void printHand(struct gameState *, int);
void printDiscard(struct gameState *, int);
void printDeck(struct gameState *, int);
void unitTestSuite(struct gameState *, struct gameState *, int);
void setSupply(struct gameState *, int, int);
int handContains(struct gameState *, int, int);
int discardContains(struct gameState *, int, int);
int deckContains(struct gameState *, int, int);

int main(){

	// Declare local variables:
	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState Game, TestGame;

	// Create instance of a game:
	initializeGame(PLAYERS, cards, SEED, &Game);
	printf("\n*** INITIALIZING %s FUNCTION UNIT TESTS ***\n\n", TESTFUN);

	// CONDITION 1: Supply card added is not empty and is in play:
	printf("*** %s FUNCTION CONDITION 1: Supply card added is not empty and is in play ***\n\n", TESTFUN);
	printf("Testing using a %s card:\n\n", CUR_CARD);
	
	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame, CUR_ENUM);

	// CONDITION 2: Supply card added is in play, but the pile is empty:
	printf("\n\n*** %s FUNCTION CONDITION 2: Supply card added is in play, but pile is empty ***", TESTFUN);
	setSupply(&Game, SMI_ENUM, FALSE);
	printf("Removing all %s cards:\n\n", SMI_CARD);
	
	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame, SMI_ENUM);

	// CONDITION 3: Supply card added is not in play:
	printf("\n\n*** %s FUNCTION CONDITION 3: Supply card added is not in play ***", TESTFUN);
	printf("Testing using a %s card:\n\n", REM_CARD);
	
	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame, REM_ENUM);

	return 0;
}

void unitTestSuite(struct gameState *Game, struct gameState *TestGame, int card){

	// Declare local variables:
	int testResult = SEED;
	int actualResult;
	int actualCount;
	int actualCard;
	int actualDisc;
	int actualDeck;

	// Determine what results should be:
	if(card == CUR_ENUM)
		actualResult = SUCCESS;
	else
		actualResult = VOID;

	printf("*** TESTING CONDITION ***\n\n");

	// Add a card to the player discard deck:
	testResult = gainCard(card, TestGame, DISC_FLAG, THIS_PLAYER);
	printf("*** Adding card to player discard: ***\n\n");

	// Return result should indicate success of attempt:
	printf("Return result of calling function: %d; should be: %d\n", testResult, actualResult);
	assertTrue(testResult == actualResult);

	// Game state: One card should have been added to the player discard:
	actualCount = Game->discardCount[THIS_PLAYER];
	if(actualResult == SUCCESS)
		actualCount = actualCount + ADD_CARD;

	printf("\nNumber of cards in the player discard: %d; should be %d",
		TestGame->discardCount[THIS_PLAYER], actualCount);
	printf("\nGAME STATE: Player discard should have gained a card (if possible to add card) - ");
	assertTrue(TestGame->discardCount[THIS_PLAYER] == actualCount);

	// Game state: Player discard should now contain the card
	printf("\nPlayer discard is:\n");
	printDiscard(TestGame, THIS_PLAYER);
	printf("\nGAME STATE: Player discard should now contain card (if possible to add card) - ");
	
	if(actualResult == SUCCESS)
		assertTrue(discardContains(TestGame, THIS_PLAYER, card));
	else
		assertTrue(!discardContains(TestGame, THIS_PLAYER, card));

	// Game state: Supply card pile decrements:
	actualCard = Game->supplyCount[card];
	if(actualResult == SUCCESS)
		actualCard = actualCard - ADD_CARD;

	printf("\nSupply card pile is: %d; should be %d",
		TestGame->supplyCount[card], actualCard);
	printf("\nGAME STATE: Supply card pile should decrement (if possible to add card) - ");
	assertTrue(TestGame->supplyCount[card] == actualCard);

	// Game state: Player deck should not have changed:
	printf("\nNumber of cards in the player deck: %d; should be: %d", 
		TestGame->deckCount[THIS_PLAYER], Game->deckCount[THIS_PLAYER]);
	printf("\nGAME STATE: No changes to the player deck - ");
	assertTrue(TestGame->deckCount[THIS_PLAYER] == Game->deckCount[THIS_PLAYER]);

	// Game state: Player hand should not have changed:
	printf("\nNumber of cards in the player hand: %d; should be: %d", 
		TestGame->handCount[THIS_PLAYER], Game->handCount[THIS_PLAYER]);
	printf("\nGAME STATE: No changes to the player hand - ");
	assertTrue(TestGame->handCount[THIS_PLAYER] == Game->handCount[THIS_PLAYER]);

	// Add a card to the player deck:
	testResult = gainCard(card, TestGame, DECK_FLAG, THIS_PLAYER);
	printf("\n*** Adding card to player deck: ***\n\n");

	// Return result should indicate success of attempt:
	printf("Return result of calling function: %d; should be: %d\n", testResult, actualResult);
	assertTrue(testResult == actualResult);

	// Game state: One card should have been added to the player deck:
	actualCount = Game->deckCount[THIS_PLAYER]; 
	if(actualResult == SUCCESS)
		actualCount = actualCount + ADD_CARD;

	printf("\nNumber of cards in the player deck: %d; should be %d",
		TestGame->deckCount[THIS_PLAYER], actualCount);
	printf("\nGAME STATE: Player deck should have gained a card (if possible to add card) - ");
	assertTrue(TestGame->deckCount[THIS_PLAYER] == actualCount);

	// Game state: Player deck should now contain the card
	printf("\nPlayer deck is:\n");
	printDeck(TestGame, THIS_PLAYER);
	printf("\nGAME STATE: Player deck should now contain card (if possible to add card) - ");
	
	if(actualResult == SUCCESS)
		assertTrue(deckContains(TestGame, THIS_PLAYER, card));
	else
		assertTrue(!deckContains(TestGame, THIS_PLAYER, card));
	
	// Game state: Supply card pile decrements:	
	if(actualResult == SUCCESS)
		actualCard = actualCard - ADD_CARD;

	printf("\nSupply card pile is: %d; should be %d",
		TestGame->supplyCount[card], actualCard);
	printf("\nGAME STATE: Supply card pile should decrement (if possible to add card) - ");
	assertTrue(TestGame->supplyCount[card] == actualCard);

	// Game state: Player discard should not have changed:
	actualDisc = Game->discardCount[THIS_PLAYER];
	if(actualResult == SUCCESS)
		actualDisc = actualDisc + ADD_CARD;

	printf("\nNumber of cards in the player discard: %d; should be: %d", 
		TestGame->discardCount[THIS_PLAYER], actualDisc);
	printf("\nGAME STATE: No changes to the player discard - ");
	assertTrue(TestGame->discardCount[THIS_PLAYER] == actualDisc);

	// Game state: Player hand should not have changed:
	printf("\nNumber of cards in the player hand: %d; should be: %d", 
		TestGame->handCount[THIS_PLAYER], Game->handCount[THIS_PLAYER]);
	printf("\nGAME STATE: No changes to the player hand - ");
	assertTrue(TestGame->handCount[THIS_PLAYER] == Game->handCount[THIS_PLAYER]);

	// Add a card to the player hand:
	testResult = gainCard(card, TestGame, HAND_FLAG, THIS_PLAYER);
	printf("\n*** Adding card to player hand: ***\n\n");

	// Return result should indicate success of attempt:
	printf("Return result of calling function: %d; should be: %d\n", testResult, actualResult);
	assertTrue(testResult == actualResult);

	// Game state: One card should have been added to the player hand:
	actualCount = Game->handCount[THIS_PLAYER];
	if(actualResult == SUCCESS)
		actualCount = actualCount + ADD_CARD;

	printf("\nNumber of cards in the player hand: %d; should be %d",
		TestGame->handCount[THIS_PLAYER], actualCount);
	printf("\nGAME STATE: Player hand should have gained a card (if possible to add card) - ");
	assertTrue(TestGame->handCount[THIS_PLAYER] == actualCount);
	
	// Game state: Player hand should now contain the card
	printf("\nPlayer hand is:\n");
	printHand(TestGame, THIS_PLAYER);
	printf("\nGAME STATE: Player hand should now contain card (if possible to add card) - ");
	
	if(actualResult == SUCCESS)
		assertTrue(handContains(TestGame, THIS_PLAYER, card));
	else
		assertTrue(!handContains(TestGame, THIS_PLAYER, card));

	// Game state: Supply card pile decrements:
	if(actualResult == SUCCESS)
		actualCard = actualCard - ADD_CARD;

	printf("\nSupply card pile is: %d; should be %d",
		TestGame->supplyCount[card], actualCard);
	printf("\nGAME STATE: Supply card pile should decrement (if possible to add card) - ");
	assertTrue(TestGame->supplyCount[card] == actualCard);

	// Game state: Player discard should not have changed:
	printf("\nNumber of cards in the player discard: %d; should be: %d", 
		TestGame->discardCount[THIS_PLAYER], actualDisc);
	printf("\nGAME STATE: No changes to the player discard - ");
	assertTrue(TestGame->discardCount[THIS_PLAYER] == actualDisc);

	// Game state: Player deck should not have changed:
	actualDeck = Game->deckCount[THIS_PLAYER];
	if(actualResult == SUCCESS)
		actualDeck = actualDeck + ADD_CARD;
	printf("\nNumber of cards in the player deck: %d; should be: %d", 
		TestGame->deckCount[THIS_PLAYER], actualDeck);
	printf("\nGAME STATE: No changes to the player deck - ");
	assertTrue(TestGame->deckCount[THIS_PLAYER] == actualDeck);

	// Game state: Opponent hand should not have changed:
	printf("\n\nNumber of cards in the opponent hand: %d; should be: %d", 
		TestGame->handCount[THAT_PLAYER], Game->handCount[THAT_PLAYER]);
	printf("\nGAME STATE: No changes to the opponent hand - ");
	assertTrue(TestGame->handCount[THAT_PLAYER] == Game->handCount[THAT_PLAYER]);

	// Game state: Opponent deck should not have changed:
	printf("\n\nNumber of cards in the opponent deck: %d; should be: %d", 
		TestGame->deckCount[THAT_PLAYER], Game->deckCount[THAT_PLAYER]);
	printf("\nGAME STATE: No changes to the opponent deck - ");
	assertTrue(TestGame->deckCount[THAT_PLAYER] == Game->deckCount[THAT_PLAYER]);

	// Game state: Opponent discard should not have changed:
	printf("\n\nNumber of cards in the opponent discard: %d; should be: %d", 
		TestGame->discardCount[THAT_PLAYER], Game->discardCount[THAT_PLAYER]);
	printf("\nGAME STATE: No changes to the opponent discard - ");
	assertTrue(TestGame->discardCount[THAT_PLAYER] == Game->discardCount[THAT_PLAYER]);

	if(actualResult == 0){
		// Game state: No changes to other victory card piles:
		printf("\n\nGAME STATE: No changes to other Victory cards:");
		printSupply(Game, TestGame, estate, copper);

		// Game state: No changes to treasure card piles:
		printf("\n\nGAME STATE: No changes to treasure cards:");
		printSupply(Game, TestGame, copper, adventurer);

		// Game state: No changes to kingdom card piles:
		printf("\n\nGAME STATE: No changes to kingdom cards:");
		printSupply(Game, TestGame, adventurer, treasure_map + 1);
	}
	else{
		// Game state: No changes to any victory, kingdom or treasure cards:
		printf("\n\nGAME STATE: No changes to any supply card piles:");
		printSupply(Game, TestGame, curse, treasure_map + 1);
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

void setSupply(struct gameState *game, int card, int num){

	// Set the number for the specified card to the supply:
	game->supplyCount[card] = num;
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

