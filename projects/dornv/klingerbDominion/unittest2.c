/* Program Filename: unittest2.c
 * Author: Barbara Jane Klinger
 * Date: 10/18/2017
 * Description: Unit tests for the isGameOver Dominion function.
 * Input: None.
 * Output: This program implements unit testing for the isGameOver function
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
#define TESTFUN "isGameOver"
#define PROV_CARD "province"
#define PROV_ENUM 3
#define CUR_CARD "curse"
#define CUR_ENUM 0
#define SMI_CARD "smithy"
#define SMI_ENUM 13
#define TM_CARD "treasure_map"
#define TM_ENUM 26
#define PLAYERS 2
#define FALSE 0
#define TRUE 1
#define SEED 10
#define VOID -1

// Function prototypes:
void assertTrue(int);
void printSupply(struct gameState *, struct gameState *, int, int);
void unitTestSuite(struct gameState *, struct gameState *);
void setSupply(struct gameState *, int, int);

int main(){

	// Declare local variables:
	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState Game, TestGame;

	// Create instance of a game:
	initializeGame(PLAYERS, cards, SEED, &Game);
	printf("\n*** INITIALIZING %s FUNCTION UNIT TESTS ***\n\n", TESTFUN);

	// CONDITION 1: All supply piles contain cards:
	printf("*** %s FUNCTION CONDITION 1: All supply piles contains at least one card ***", TESTFUN);
	setSupply(&Game, PROV_ENUM, TRUE);
	setSupply(&Game, CUR_ENUM, TRUE);
	setSupply(&Game, SMI_ENUM, TRUE);
	setSupply(&Game, TM_ENUM, TRUE);

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 2: Province card pile empty:
	printf("\n\n*** %s FUNCTION CONDITION 2: Only provience card stack empty ***", TESTFUN);
	setSupply(&Game, PROV_ENUM, FALSE);

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 3: Two non-provience card piles empty:
	printf("\n\n*** %s FUNCTION CONDITION 2: Two non-provience card stacks empty ***", TESTFUN);
	setSupply(&Game, PROV_ENUM, TRUE);
	setSupply(&Game, CUR_ENUM, FALSE);
	setSupply(&Game, SMI_ENUM, FALSE);

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	// CONDITION 4: Three non-provience card piles empty (at supply card boundaries):
	printf("\n\n*** %s FUNCTION CONDITION 2: Three non-provience card stacks empty at boundaries ***", TESTFUN);
	setSupply(&Game, TM_ENUM, FALSE);

	// Copy game instance to test case:
	memcpy(&TestGame, &Game, sizeof(struct gameState));

	// Run unit test suite:
	unitTestSuite(&Game, &TestGame);

	return 0;
}

void unitTestSuite(struct gameState *Game, struct gameState *TestGame){

	// Declare local variables:
	int gameStatus = VOID;
	int testStatus = VOID;

	// Run the isGameOver function to determine if the the test game is over:
	testStatus = isGameOver(TestGame);

	// Determine the actual status of the game:
	if(Game->supplyCount[PROV_ENUM] == FALSE)
		gameStatus = TRUE;
	else if(Game->supplyCount[CUR_ENUM] == FALSE && Game->supplyCount[SMI_ENUM] == FALSE && Game->supplyCount[TM_ENUM] == FALSE)
		gameStatus = TRUE;
	else
		gameStatus = FALSE;

	printf("\n\n*** TESTING CONDITION ***");

	// Game state: The function should correctly return if the game is over or not:
	printf("\n\nTest game status: %d; should be: %d", testStatus, gameStatus);
	printf("\nGAME STATE: function should return correct status of game - ");
	assertTrue(testStatus == gameStatus);

	// Game state: Supply pile contents should not have been modified:
	printf("\n\nGAME STATE: No changes to any supply card piles - ");
	printSupply(Game, TestGame, CUR_ENUM, TM_ENUM + 1); 
}

void setSupply(struct gameState *game, int card, int num){

	// Set the number for the specified card to the supply:
	game->supplyCount[card] = num;
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


