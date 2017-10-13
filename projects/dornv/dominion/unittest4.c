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

//int endTurn(struct gameState *state

int main() {
	int i;
    int seed = 37;
    int numPlayer = 2;
	int k[10] = {adventurer, village, mine, smithy, council_room, feast, gardens, remodel, baron, great_hall};
	
	struct gameState state;
	initializeGame(2, k, seed, &state);
	int whoseTurn = state.whoseTurn;	//saving player 1
	
	/****************************************************/
	printf("Running unit test 4.1\n");
	//normal end turn starting with player 1
	endTurn(&state);
	assert(state.handCount[whoseTurn] == 0);
	assert(whoseTurn == whoseTurn);
	assert(state.outpostPlayed == 0);
	assert(state.phase == 0);
	assert(state.numActions == 1);
	assert(state.numBuys == 1);
	assert(state.playedCardCount == 0);
	assert(state.handCount[whoseTurn] == 0);
	
	/****************************************************/
	printf("Running unit test 4.2\n");
	//normal end turn starting with player 2
	endTurn(&state);
	assert(state.handCount[whoseTurn + 1] == 0);
	assert(whoseTurn == whoseTurn);
	assert(state.outpostPlayed == 0);
	assert(state.phase == 0);
	assert(state.numActions == 1);
	assert(state.numBuys == 1);
	assert(state.playedCardCount == 0);
	assert(state.handCount[whoseTurn + 1] == 0);
	
	/****************************************************/
	printf("Running unit test 4.3\n");
	//Ending turn after getting coin and buying a card
	state.coins = 10;
	buyCard(1, &state);
	endTurn(&state);
	assert(state.handCount[whoseTurn] == 0);
	assert(whoseTurn == whoseTurn);
	assert(state.outpostPlayed == 0);
	assert(state.phase == 0);
	assert(state.numActions == 1);
	assert(state.coins == (10 - getCost[1]);
	assert(state.numBuys == 1);
	assert(state.playedCardCount == 0);
	assert(state.handCount[whoseTurn] == 0);
	
	printf("All tests passed!\n");
	
	return 0;
}