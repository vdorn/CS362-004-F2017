/* -----------------------------------------------------------------------
 * Unit test for the initializeGame() function within dominion.c
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 37;
    int numPlayer = 2;
	int k[10] = {adventurer, village, mine, smithy, council_room, feast, gardens, remodel, baron, great_hall};
	
	//supplies and proviences should be set to 8 for two player game
	int supplyCount = 8;
	int provienceCount = 8;
	
    struct gameState state;
	
	//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)
    printf ("TESTING initializeGame():\n");
	
	/****************************************************/
	printf("Running unit test 2.1\n");
	int status = initializeGame(2, k, seed, &state);
	
	//bailing out if the game failed to initialize
	assert(status == 0);
	
	//checking number of players
	assert(state->numPlayer == numPlayer);
	
	//checking curse count
	assert(state->supplyCount[curse] = 10);
	
	//checking for correct supply counts
	for(i = 0; i < 10; i++){
		assert(state->supplyCount[i] == supplyCount);
	}
	
	//checking for decks set to zero
	for(i = 0; i < 2; i++){
		assert(state->deckCount[i] == 10);
	}
	
	//checking discard pile
	assert(state->discardCount[i] == 0);
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		assert(state->embargoTokens[i] == 0);
    }
	
	//checking player 1 setup
	assert(state->outpostPlayed == 0);
	assert(state->phase == 0);
	assert(state->numActions == 1);
	assert(state->numBuys == 1);
	assert(state->playedCardCount == 0);
	assert(state->whoseTurn == 0);
	assert(state->handCount[state->whoseTurn] == 0);
	
	/****************************************************/
	//setting up values for 4 player game
	supplyCount = 12;
	provienceCount = 12;
	
	printf("Running unit test 2.2\n");
	//running test 2.1 with 4 player count
	int status = initializeGame(4, k, seed, &state);
	
	//bailing out if the game failed to initialize
	assert(status == 0);
	
	//checking number of players
	assert(state->numPlayer == numPlayer);
	
	//checking curse count
	assert(state->supplyCount[curse] = 10);
	
	//checking for correct supply counts
	for(i = 0; i < 10; i++){
		assert(state->supplyCount[i] == supplyCount);
	}
	
	//checking for decks set to zero
	for(i = 0; i < 2; i++){
		assert(state->deckCount[i] == 10);
	}
	
	//checking discard pile
	assert(state->discardCount[i] == 0);
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		assert(state->embargoTokens[i] == 0);
    }
	
	//checking player 1 setup
	assert(state->outpostPlayed == 0);
	assert(state->phase == 0);
	assert(state->numActions == 1);
	assert(state->numBuys == 1);
	assert(state->playedCardCount == 0);
	assert(state->whoseTurn == 0);
	assert(state->handCount[state->whoseTurn] == 0);
	
	/****************************************************/
	printf("Running unit test 2.3\n");
	//running test 2.1 with 10 player count
	int status = initializeGame(10, k, seed, &state);
	
	//bailing out if the game failed to initialize
	assert(status == 0);
	
	//checking number of players
	assert(state->numPlayer == numPlayer);
	
	//checking curse count
	assert(state->supplyCount[curse] = 10);
	
	//checking for correct supply counts
	for(i = 0; i < 10; i++){
		assert(state->supplyCount[i] == supplyCount);
	}
	
	//checking for decks set to zero
	for(i = 0; i < 2; i++){
		assert(state->deckCount[i] == 10);
	}
	
	//checking discard pile
	assert(state->discardCount[i] == 0);
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		assert(state->embargoTokens[i] == 0);
    }
	
	//checking player 1 setup
	assert(state->outpostPlayed == 0);
	assert(state->phase == 0);
	assert(state->numActions == 1);
	assert(state->numBuys == 1);
	assert(state->playedCardCount == 0);
	assert(state->whoseTurn == 0);
	assert(state->handCount[state->whoseTurn] == 0);

    printf("All tests passed!\n");

    return 0;
}