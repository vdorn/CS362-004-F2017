/* Program Filename: cardtest3.c
 * Author: Barbara Jane Klinger
 * Date: 10/18/2017
 * Description: Unit tests for the Sea Hag Dominion card.
 * Input: None.
 * Output: This program implements unit testing for the Sea Hag card implemented
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
#define TESTCARD "sea_hag"
#define NEWCARD "curse"
#define CARDENUM 25
#define CURENUM 0
#define SEA_CARD 1
#define CUR_CARD 1
#define DIS_CARD 1
#define HAND_POS 0
#define PLAYERS 2
#define FALSE 0
#define TRUE 1
#define SEED 10
#define THIS_PLAYER 0
#define THAT_PLAYER 1
#define OTHER_PLAYER 2

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

	// Create instance of a game:
	initializeGame(PLAYERS, cards, SEED, &Game);
	printf("\n*** INITIALIZING SEA HAG CARD UNIT TESTS ***\n\n");

	// CONDITION 1: Typical condition
	// Actions should occur as specified on the card face:
	printf("*** SEA HAG CONDITION 1: Two players with a full curse pile ***\n");
	printf("\nInitial player hand:\n");
	printHand(&Game, THIS_PLAYER);

	// Replace first card in player hand with a sea hag card:
	Game.hand[THIS_PLAYER][0] = CARDENUM;
	printf("\n\nReplacing card in player hand with %s card:\n", TESTCARD);
	printHand(&Game, THIS_PLAYER);

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 2: Special condition - no curse cards:
	printf("\n\n*** SEA HAG CONDITION 2: No curse cards remaining ***\n");
	Game.supplyCount[CURENUM] = 0;

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 3: Special condition - 2 other players, 1 curse card:
	printf("\n\n*** SEA HAG CONDITION 3: Two other players, but only 1 curse card remaining ***\n");

	// Create instance of a game with 3 players and reduce curse cards to 1:
	initializeGame(PLAYERS + 1, cards, SEED, &Game);
	Game.supplyCount[CURENUM] = 1;
	Game.hand[THIS_PLAYER][0] = CARDENUM;

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

	// Test case plays the sea hag card:
	result = cardEffect(CARDENUM, FALSE, FALSE, FALSE, TestGame, HAND_POS, &bonus);
	printf("\n\n*** TESTING CONDITION ***\n\n");
	printf("The test case has played the %s card:\n\n", TESTCARD);

	// Return result of calling cardEffect should be 0 to indicate playable action card:
	printf("Return result of playing card: %d; should be 0\n", result);
	assertTrue(!result);

	// Game state: Player hand should have discarded a card:
	printf("\nNumber of cards in the player hand: %d; should be %d",
		TestGame->handCount[THIS_PLAYER], Game->handCount[THIS_PLAYER] - SEA_CARD);
	printf("\nGAME STATE: Player hand should have discarded a card - ");
	assertTrue(TestGame->handCount[THIS_PLAYER] == (Game->handCount[THIS_PLAYER] - SEA_CARD));

	// Game state: Player hand should no longer contain sea hag card
	printf("\nPlayer hand is:\n");
	printHand(TestGame, THIS_PLAYER);
	printf("\nGAME STATE: Player hand should no longer contain %s card - ", TESTCARD);
	assertTrue(!handContains(TestGame, THIS_PLAYER, CARDENUM));

	// Game state: Player discard should gain a card:
	printf("\nNumber of cards in the player discard: %d; should be %d",
		TestGame->discardCount[THIS_PLAYER], (Game->discardCount[THIS_PLAYER] + SEA_CARD));
	printf("\nGAME STATE: Player hand should have gained a card - ");
	assertTrue(TestGame->discardCount[THIS_PLAYER] == (Game->discardCount[THIS_PLAYER] + SEA_CARD));

	// Game state: Player discard should now contain the sea hag card
	printf("\nPlayer discard is:\n");
	printDiscard(TestGame, THIS_PLAYER);
	printf("\nGAME STATE: Player discard should now contain %s card - ", TESTCARD);
	assertTrue(discardContains(TestGame, THIS_PLAYER, CARDENUM));

	// Game state: Player deck should not have changed:
	printf("\nNumber of cards in the player deck: %d; should be: %d", 
		TestGame->deckCount[THIS_PLAYER], Game->deckCount[THIS_PLAYER]);
	printf("\nGAME STATE: No changes to the player deck - ");
	assertTrue(TestGame->deckCount[THIS_PLAYER] == Game->deckCount[THIS_PLAYER]);
	printf("\nPlayer deck is:\n");
	printDeck(TestGame, THIS_PLAYER);
	printf("\nPlayer deck should be:\n");
	printDeck(Game, THIS_PLAYER);

	// Game state: Opponent hand(s) should not have changed:
	printf("\n\nNumber of cards in the opponent hand: %d; should be: %d", 
		TestGame->handCount[THAT_PLAYER], Game->handCount[THAT_PLAYER]);
	printf("\nGAME STATE: No changes to the opponent hand - ");
	assertTrue(TestGame->handCount[THAT_PLAYER] == Game->handCount[THAT_PLAYER]);
	printf("\nOpponent hand is:\n");
	printHand(TestGame, THAT_PLAYER);
	printf("\nOpponent hand should be:\n");
	printHand(Game, THAT_PLAYER);

	if(Game->numPlayers > 2){

		printf("\n\nNumber of cards in the opponent 2 hand: %d; should be: %d", 
			TestGame->handCount[OTHER_PLAYER], Game->handCount[OTHER_PLAYER]);
		printf("\nGAME STATE: No changes to the opponent 2 hand - ");
		assertTrue(TestGame->handCount[OTHER_PLAYER] == Game->handCount[OTHER_PLAYER]);
		printf("\nOpponent 2 hand is:\n");
		printHand(TestGame, THAT_PLAYER);
		printf("\nOpponent 2 hand should be:\n");
		printHand(Game, THAT_PLAYER);

	}

	// Game state: State of opponents deck depends on condition:
	if(Game->supplyCount[CURENUM] == 0){

		// Game state: The number of cards in the opponent deck should have decreased:
		printf("\n\nNumber of cards in the opponent deck: %d; should be: %d", 
			TestGame->deckCount[THAT_PLAYER], Game->deckCount[THAT_PLAYER] - DIS_CARD);
		printf("\nGAME STATE: Number of cards in opponents deck should decrease by %d - ",
			DIS_CARD);
		assertTrue(TestGame->deckCount[THAT_PLAYER] == Game->deckCount[THAT_PLAYER] - DIS_CARD);
	}
	else {
		// Game state: The number of cards in the opponent deck should not have changed:
		printf("\n\nNumber of cards in the opponent deck: %d; should be: %d", 
			TestGame->deckCount[THAT_PLAYER], Game->deckCount[THAT_PLAYER]);
		printf("\nGAME STATE: No changes to the number of cards in opponent deck - ");
		assertTrue(TestGame->deckCount[THAT_PLAYER] == Game->deckCount[THAT_PLAYER]);


		// Game state: The top card of the opponent deck should now be a curse card:
		printf("\nOpponent deck is:\n");
		printDeck(TestGame, THAT_PLAYER);
		printf("\nGAME STATE: Opponent deck should contain a %s card - ", NEWCARD);
		assertTrue(deckContains(TestGame, THAT_PLAYER, CURENUM));
	}

	if(Game->numPlayers > 2){

		// Game state: The number of cards in the opponent 2 deck should have decreased:
		printf("\n\nNumber of cards in the opponent 2 deck: %d; should be: %d", 
			TestGame->deckCount[OTHER_PLAYER], Game->deckCount[OTHER_PLAYER] - DIS_CARD);
		printf("\nGAME STATE: Number of cards in opponent 2 deck should decrease by %d - ",
			DIS_CARD);
		assertTrue(TestGame->deckCount[OTHER_PLAYER] == Game->deckCount[OTHER_PLAYER] - DIS_CARD);	
	}

	// Game state: Opponent discard should contain an additional card:
	printf("\n\nNumber of cards in the opponent discard: %d; should be: %d",
		TestGame->discardCount[THAT_PLAYER], (Game->discardCount[THAT_PLAYER] + DIS_CARD));
	printf("\nGAME STATE: Number of cards in opponent discard should increase by %d - ",
		DIS_CARD);
	assertTrue(TestGame->discardCount[THAT_PLAYER] == (Game->discardCount[THAT_PLAYER] + DIS_CARD));

	if(Game->numPlayers > 2){

		// Game state: Opponent 2 discard should contain an additional card:
		printf("\n\nNumber of cards in the opponent 2 discard: %d; should be: %d", 
			TestGame->discardCount[OTHER_PLAYER], Game->discardCount[OTHER_PLAYER] + DIS_CARD);
		printf("\nGAME STATE: Number of cards in opponent 2 discard should increase by %d - ",
			DIS_CARD);
		assertTrue(TestGame->deckCount[OTHER_PLAYER] == Game->deckCount[OTHER_PLAYER] + DIS_CARD);	
	}

	// Game state: Check amount of curse cards remaining
	if(Game->supplyCount[CURENUM] == 0){

		// Game state: If there were no curse cards to play, there should be no change:
		printf("\n\nNumber of curse cards remaining: %d; should be: %d",
			TestGame->supplyCount[CURENUM], Game->supplyCount[CURENUM]);
		printf("\nGAME STATE: All curse cards in play - should be 0 - ");
		assertTrue(TestGame->supplyCount[CURENUM] == Game->supplyCount[CURENUM]);

	}
	else if(Game->numPlayers > 2){
	
		// Game state: Last remaining curse card should removed from victory pile:
		printf("\n\nNumber of curse cards remaining: %d; should be: %d",
			TestGame->supplyCount[CURENUM], Game->supplyCount[CURENUM] - CUR_CARD);
		printf("\nGAME STATE: All curse cards now in play - should be 0 - ");
		assertTrue(TestGame->supplyCount[CURENUM] == Game->supplyCount[CURENUM] - CUR_CARD);
	}
	else{
		// Game state: Curse cards should have been removed from the corresponding victory pile:
		printf("\n\nNumber of curse cards remaining: %d; should be: %d",
			TestGame->supplyCount[CURENUM], (Game->supplyCount[CURENUM] - (PLAYERS - 1)));
		printf("\nGAME STATE: %d curse cards should have been removed from victory pile - ",
			(PLAYERS - 1));
		assertTrue(TestGame->supplyCount[CURENUM] == (Game->supplyCount[CURENUM] - (PLAYERS - 1)));
	}

	// Game state: There should be no changes treasure or kingdom cards or any other victory cards:
	printf("\n\nGAME STATE: No changes to other victory or treasure or kingdom cards - ");
	printSupply(Game, TestGame, estate, treasure_map + 1); 	
	
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


