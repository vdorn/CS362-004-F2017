/* -----------------------------------------------------------------------
 * Unit test for the endTurn() function within dominion.c
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//int endTurn(struct gameState *state)

int main() {
    int seed = 37;
	int k[10] = {adventurer, village, mine, smithy, council_room, feast, gardens, remodel, baron, great_hall};
	int testPassed = 0;
	int passed = 0;
	
	struct gameState state;
	initializeGame(2, k, seed, &state);
	int whoseTurn = state.whoseTurn;	//saving player 1
	
	printf ("TESTING endTurn():\n");
	
	/****************************************************/
	printf("Running unit test 4.1: Normal End Turn Player 1\n");
	//normal end turn starting with player 1
	int returnValue = endTurn(&state);
	if(returnValue != 0){
		passed = 1;
		printf("End Turn returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[whoseTurn] == 0);
	if(state.handCount[whoseTurn] != 0){
		passed = 1;
		printf("Next players hand count returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.whoseTurn == whoseTurn);
	if(state.whoseTurn != whoseTurn + 1){
		passed = 1;
		printf("WhoseTurn: %d, Expected: %d\n", state.whoseTurn, whoseTurn + 1);	//player one turn ended, now player 2
	}
	
	//assert(state.outpostPlayed == 0);
	if(state.outpostPlayed != 0){
		passed = 1;
		printf("Outpost Player: %d, Expected: %d\n", state.outpostPlayed, 0);
	}
	
	//assert(state.phase == 0);
	if(state.phase != 0){
		passed = 1;
		printf("Phase: %d, Expected: %d\n", state.phase, 0);
	}
	
	//assert(state.numActions == 1);
	if(state.numActions != 1){
		passed = 1;
		printf("Num Actions: %d, Expected: %d\n", state.numActions, 1);
	}
	
	//assert(state.numBuys == 1);
	if(state.numBuys != 1){
		passed = 1;
		printf("Num Buys: %d, Expected: %d\n", state.numBuys, 1);
	}
	
	//assert(state.playedCardCount == 0);
	if(state.playedCardCount != 0){
		passed = 1;
		printf("Played Card Count: %d, Expected: %d\n", state.playedCardCount, 0);
	}
	
	//assert(state.handCount[whoseTurn] == 0);
	if(state.handCount[whoseTurn] != 0){
		passed = 1;
		printf("Played Hand Count: %d, Expected: %d\n", state.handCount[whoseTurn], 0);
	}
	
	//assert(state.coins >= 0);
	if(state.coins < 0){
		passed = 1;
		printf("Coins: %d, Expected: >= 0\n", state.coins);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/****************************************************/
	printf("Running unit test 4.2: Normal End Turn Player 2\n");
	passed = 0;
	//normal end turn starting with player 2
	returnValue = endTurn(&state);
	if(returnValue != 0){
		passed = 1;
		printf("End Turn returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[whoseTurn + 1] == 0);
	if(state.handCount[whoseTurn + 1] != 0){
		passed = 1;
		printf("Next players hand count returned: %d, Expected: %d\n", state.handCount[whoseTurn + 1], 0);
	}
	
	//assert(whoseTurn == whoseTurn);
	if(state.whoseTurn != whoseTurn){
		passed = 1;
		printf("WhoseTurn: %d, Expected: %d\n", state.whoseTurn, whoseTurn);
	}
	
	//assert(state.outpostPlayed == 0);
	if(state.outpostPlayed != 0){
		passed = 1;
		printf("Outpost Player: %d, Expected: %d\n", state.outpostPlayed, 0);
	}
	
	//assert(state.phase == 0);
	if(state.phase != 0){
		passed = 1;
		printf("Phase: %d, Expected: %d\n", state.phase, 0);
	}
	
	//assert(state.numActions == 1);
	if(state.numActions != 1){
		passed = 1;
		printf("Num Actions: %d, Expected: %d\n", state.numActions, 1);
	}
	
	//assert(state.numBuys == 1);
	if(state.numBuys != 1){
		passed = 1;
		printf("Num Buys: %d, Expected: %d\n", state.numBuys, 1);
	}
	
	//assert(state.playedCardCount == 0);
	if(state.playedCardCount != 0){
		passed = 1;
		printf("Played Card Count: %d, Expected: %d\n", state.playedCardCount, 0);
	}
	
	//assert(state.handCount[whoseTurn + 1] == 0);
	if(state.handCount[whoseTurn + 1] != 0){
		passed = 1;
		printf("Played Hand Count: %d, Expected: %d\n", state.handCount[whoseTurn + 1], 0);
	}
	
	//assert(state.coins >= 0);
	if(state.coins < 0){
		passed = 1;
		printf("Coins: %d, Expected: >= 0\n", state.coins);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/****************************************************/
	printf("Running unit test 4.3: Ending Turn After Buying a Card\n");
	passed = 0;
	//Ending turn after getting coin and buying a card
	state.coins = 10;
	buyCard(1, &state);
	returnValue = endTurn(&state);
	if(returnValue != 0){
		passed = 1;
		printf("End Turn returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[whoseTurn] == 0);
	if(state.handCount[whoseTurn] != 0){
		passed = 1;
		printf("Next players hand count returned: %d, Expected: %d\n", state.handCount[whoseTurn], 0);
	}
	
	//assert(whoseTurn == whoseTurn);
	if(state.whoseTurn != whoseTurn + 1){
		passed = 1;
		printf("WhoseTurn: %d, Expected: %d\n", state.whoseTurn, whoseTurn + 1);
	}
	
	//assert(state.outpostPlayed == 0);
	if(state.outpostPlayed != 0){
		passed = 1;
		printf("Outpost Player: %d, Expected: %d\n", state.outpostPlayed, 0);
	}
	
	//assert(state.phase == 0);
	if(state.phase != 0){
		passed = 1;
		printf("Phase: %d, Expected: %d\n", state.phase, 0);
	}
	
	//assert(state.numActions == 1);
	if(state.numActions != 1){
		passed = 1;
		printf("Num Actions: %d, Expected: %d\n", state.numActions, 1);
	}
	
	//assert(state.numBuys == 1);
	if(state.numBuys != 1){
		passed = 1;
		printf("Num Buys: %d, Expected: %d\n", state.numBuys, 1);
	}
	
	//assert(state.playedCardCount == 0);
	if(state.playedCardCount != 0){
		passed = 1;
		printf("Played Card Count: %d, Expected: %d\n", state.playedCardCount, 0);
	}
	
	//assert(state.handCount[whoseTurn] == 0);
	if(state.handCount[whoseTurn] != 0){
		passed = 1;
		printf("Played Hand Count: %d, Expected: %d\n", state.handCount[whoseTurn], 0);
	}
	
	//assert(state.coins >= 0);
	if(state.coins < 0){
		passed = 1;
		printf("Coins: %d, Expected: >= 0\n", state.coins);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	printf("Passing Tests: %d/3\n", testPassed);
	
	return 0;
}