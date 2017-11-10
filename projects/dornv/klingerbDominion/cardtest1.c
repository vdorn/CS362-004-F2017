/* Program Filename: cardtest1.c
 * Author: Barbara Jane Klinger
 * Date: 10/18/2017
 * Description: Unit tests for the Adventurer Dominion card.
 * Input: None.
 * Output:  This program implements unit testing for the Adventurer card implemented 
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
#define TESTCARD "adventurer"
#define CARDENUM 7
#define COIN_CARD 2
#define COIN_CARD_1 1
#define COIN_CARD_0 0
#define ADV_CARD 1
#define HAND_POS 0
#define PLAYERS 2
#define FALSE 0
#define SEED 10
#define THIS_PLAYER 0
#define THAT_PLAYER 1

// Function prototypes:
void assertTrue(int);
void printSupply(struct gameState *, struct gameState *, int, int);
int printHand(struct gameState *, int *);
int printDiscard(struct gameState *);
void printDeck(struct gameState *);
void testCaseSuite(struct gameState *, struct gameState*, int);

int main() {

	// Declare local variables:
	int dummy = 0;
	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy};
	struct gameState Game, TestGame; 	

	// Create instance of a game:
	initializeGame(PLAYERS, cards, SEED, &Game);
	printf("\n***CREATING NEW DOMINION GAME***\n\n"); 
	
	// CONDITION 1: At least 2 treasure cards are present in the player deck
	printf("***ADVENTURER CONDITION 1: At least 2 treasure cards present in player deck***\n");
	printf("\nInitial player hand:\n");
	printHand(&Game, &dummy);

	printf("\nInitial player deck:\n");
	printDeck(&Game);

	// Replace first card in hand with an Adventurer card and print to display:
	Game.hand[THIS_PLAYER][0] = CARDENUM;
	printf("\n\nReplacing first hand card with %s card:\n", TESTCARD);
	printHand(&Game, &dummy);

	// Copy game instance to a test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run test suite on this test instance:
	testCaseSuite(&Game, &TestGame, COIN_CARD);

	// CONDITION 2: One treasure card in the player's discard, but none in the deck pile
	// necessitating a shuffle and a termination after no additional treasure is found:
	printf("\n\n***ADVENTURER CONDITION 2: 0 treasure cards in the player deck, 1 in the discard pile***\n");
	printf("This condition necessitates the use of shuffle and then termination when no additional treasure found.\n");

	// Remove a treasure card from the discard pile:
	Game.discard[THIS_PLAYER][1] = -1;
	Game.discardCount[THIS_PLAYER]--;
	printf("\n\nRemoving one treasure card from the discard pile:\n");
	printDiscard(&Game);

	// Copy new game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run test suite on this test instance:
	testCaseSuite(&Game, &TestGame, COIN_CARD_1);

	// Condition 3: 0 treasure cards in the player deck and 0 in the discard pile
	// necessitating a shuffle and termination after no treasure is found:
	printf("\n\n***ADVENTURER CONDITION 3: 0 treasure card in the player deck, 0 in the discard pile***\n");
	printf("This condition necessitates the use of shuffle and then termination when no treasure is found.\n");

	// Remove a treasure card to the player deck:
	Game.deck[THIS_PLAYER][1] = 1;
	printf("\n\nReplacing the copper treasure card with an estate card in the player deck:\n");
	printDeck(&Game);

	// Copy modified game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run test suit on this test instance:
	testCaseSuite(&Game, &TestGame, COIN_CARD_0);

	return 0;
}

void testCaseSuite(struct gameState *Game, struct gameState *TestGame, int coinCards){

	// Declare local variables:
	int action = SEED;
	int bonus = 0;
	int treasure = 0;
	int testTreasure = 0;

	// Test case plays adventurer card:
	action = cardEffect(CARDENUM, FALSE, FALSE, FALSE, TestGame, HAND_POS, &bonus); 
	printf("\n\n***TESTING CONDITION***\n\n");
	printf("The test case has played the %s card:\n\n", TESTCARD);

	// The cardEffect function should have returned 0 indicating a succesful action 
	// completed:
	printf("cardEffect return result of playing card: %d; success indicated by: %d\n", action, 0);
	assertTrue(!action);
	
	// Game state: Player hand has one new card as a result of gaining two treasure 
	// cards and losing one adventurer card:
	printf("\nNumber of cards in player hand: %d; should be: %d\n",
		TestGame->handCount[THIS_PLAYER], Game->handCount[THIS_PLAYER] + coinCards - ADV_CARD);
	printf("GAME STATE: Player hand has a net gain of %d - ", (coinCards - ADV_CARD));
	assertTrue(TestGame->handCount[THIS_PLAYER] == (Game->handCount[THIS_PLAYER] + coinCards - ADV_CARD)); 
	
	printf("\nStarting player hand:\n");
	printHand(Game, &treasure);

	printf("\nGAME STATE: Player hand should no longer contain %s card - \n", 
		TESTCARD);
	assertTrue(!printHand(TestGame, &testTreasure));

	printf("\nNumber of treasure cards in player hard: %d; should be: %d\n", 
		testTreasure, treasure + coinCards);
	printf("GAME STATE: Player hand should contain %d additional treasure cards - ", 
		coinCards);
	assertTrue(testTreasure == (treasure + coinCards));

	// Game state: Adventurer card is discarded at end of action:
	// If discard pile empty, print empty status of set:
	if(TestGame->discardCount[THIS_PLAYER] == 0)
		printf("\nEmpty discard set.");

	// Print contents of the player's discard pile:
	printf("\nGAME STATE: Player discard pile should contain %s card - \n", TESTCARD);
	assertTrue(printDiscard(TestGame));

	// Game state: Combined value of deck and discard piles should have net loss of one
	// as a result of adding 1 adventurer card and subtracting 2 treasure cards:
	printf("\nCombined value of player deck and discard piles: %d; should be: %d\n",
		(TestGame->deckCount[THIS_PLAYER] + TestGame->discardCount[THIS_PLAYER]), 
		(Game->deckCount[THIS_PLAYER] + Game->discardCount[THIS_PLAYER] + ADV_CARD - coinCards));
	printf("GAME STATE: The player deck and discard piles should have a combined net gain of %d - ", 
		(ADV_CARD - coinCards));
	assertTrue((TestGame->deckCount[THIS_PLAYER] + TestGame->discardCount[THIS_PLAYER]) ==
		(Game->deckCount[THIS_PLAYER] + Game->discardCount[THIS_PLAYER] + ADV_CARD - coinCards));

	// Game state: No changes to other player's hand/deck/discard:
	printf("\nOther player's hand: %d; should be: %d\n", TestGame->handCount[THAT_PLAYER],
		Game->handCount[THAT_PLAYER]);
	printf("GAME STATE: There should be no changes to the other player's hand - ");
	assertTrue(TestGame->handCount[THAT_PLAYER] == Game->handCount[THAT_PLAYER]);

	printf("\nOther player's deck: %d; should be: %d\n", TestGame->deckCount[THAT_PLAYER],
		Game->deckCount[THAT_PLAYER]);
	printf("GAME STATE: There should be no changes to the other player's deck - ");
	assertTrue(TestGame->deckCount[THAT_PLAYER] == Game->deckCount[THAT_PLAYER]);

	printf("\nOther player's discard: %d; should be: %d\n", TestGame->discardCount[THAT_PLAYER],
		Game->discardCount[THAT_PLAYER]);
	printf("GAME STATE: There should no changes to the other player's discards - ");
	assertTrue(TestGame->discardCount[THAT_PLAYER] == Game->discardCount[THAT_PLAYER]);

	// Game state: No cards are trashed as a result of playing an adventurer card:
	printf("\nTrashed cards: %d; should be %d", TestGame->playedCardCount, Game->playedCardCount);
	printf("\nGAME STATE: No cards should be trashed - ");
	assertTrue(TestGame->playedCardCount == Game->playedCardCount);

	// Game state: No changes to victory card piles:
	printf("\nGAME STATE: There should be no changes to the number of victory cards - ");
	printSupply(Game, TestGame, curse, (province + 1));

	// Game state: No changes to treasure card piles:
	printf("\nGAME STATE: There should be no changes to the number of treasure cards - ");
	printSupply(Game, TestGame, copper, (gold + 1));

	// Game state: No changes to kingdom cards piles:
	printf("\nGAME STATE: There should be no changes to the number of kingdom cards - ");
	printSupply(Game, TestGame, adventurer, (treasure_map + 1));
	printf("\n");
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

int printHand(struct gameState *game, int *coins){

	// Declare local variables:
	int found = FALSE;
	int index;

	// Print the enum values of the cards in the hand:
	for(index = 0; index < game->handCount[THIS_PLAYER]; index++){
		
		printf("%d, ", game->hand[THIS_PLAYER][index]);

		// Set found flag if specified enum located:
		if(game->hand[THIS_PLAYER][index] == CARDENUM)
			found = ADV_CARD;

		// Count the number of treasure cards in this hand:
		if ( game->hand[THIS_PLAYER][index] > province && game->hand[THIS_PLAYER][index] < adventurer)
			(*coins)++;
	}

	// Return flag:
	return found;
}

void printDeck(struct gameState *game){

	// Declare local variables:
	int index;

	// Print the enum values of the cards in the deck:
	for(index = 0; index < game->deckCount[THIS_PLAYER]; index++){

		printf("%d, ", game->deck[THIS_PLAYER][index]);
	}
}

int printDiscard(struct gameState *game){

	// Declare local variables: 
	int found = FALSE;
	int index;

	// Print enum values of the discard pile cards:
	for(index = 0; index < game->discardCount[THIS_PLAYER]; index++){


		printf("%d, ", game->discard[THIS_PLAYER][index]);

		// Set found flag if specified card located:
		if(game->discard[THIS_PLAYER][index] == CARDENUM)
			found = ADV_CARD;
	}

	// Return flag:
	return found;
}
