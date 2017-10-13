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
	int supplyCount = 10;
	int provienceCount = 8;
	int victoryCount = 8;
	
    struct gameState state;
	
	//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)
    printf ("TESTING initializeGame():\n");
	
	/****************************************************/
	printf("Running unit test 2.1\n");
	int status = initializeGame(2, k, seed, &state);
	
	//bailing out if the game failed to initialize
	assert(status == 0);
	
	//checking number of players
	assert(state.numPlayers == numPlayer);
	
	//checking curse count
	assert(state.supplyCount[curse] = 10);
	
	//checking for correct supply counts
	for(i = 0; i < 10; i++){
		if(i == 9 || i == 6){
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			assert(state.supplyCount[k[i]] == victoryCount);
		}
		else{
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			assert(state.supplyCount[k[i]] == supplyCount);
		}
	}
	
	//checking for decks size for player 1 (10 - 5) and player 2 (10)
	assert(state.deckCount[0] == (10 - 5));
	assert(state.deckCount[1] == 10);
	
	//checking discard pile
	assert(state.discardCount[i] == 0);
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		assert(state.embargoTokens[i] == 0);
    }
	
	//checking player 1 setup
	assert(state.outpostPlayed == 0);
	assert(state.phase == 0);
	assert(state.numActions == 1);
	assert(state.numBuys == 1);
	assert(state.playedCardCount == 0);
	assert(state.whoseTurn == 0);
	assert(state.handCount[state.whoseTurn] == 5);	//5 card hand to start
	
	/****************************************************/
	//setting up values for 4 player game
	//supplyCount = 10;
	provienceCount = 12;
	victoryCount = 12;
	numPlayer = 4;
	
	printf("Running unit test 2.2\n");
	//running test 2.1 with 4 player count
	status = initializeGame(4, k, seed, &state);
	
	//bailing out if the game failed to initialize
	assert(status == 0);
	
	//checking number of players
	assert(state.numPlayers == numPlayer);
	
	//checking curse count
	assert(state.supplyCount[curse] = 10);
	
		//checking for correct supply counts
	for(i = 0; i < 10; i++){
		if(i == 9 || i == 6){
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			assert(state.supplyCount[k[i]] == victoryCount);
		}
		else{
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			assert(state.supplyCount[k[i]] == supplyCount);
		}
	}
	
	//checking for decks size for player 1 (10 - 5) and player 2 (10)
	assert(state.deckCount[0] == (10 - 5));
	assert(state.deckCount[1] == 10);
	
	//checking discard pile
	assert(state.discardCount[i] == 0);
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		assert(state.embargoTokens[i] == 0);
    }
	
	//checking player 1 setup
	assert(state.outpostPlayed == 0);
	assert(state.phase == 0);
	assert(state.numActions == 1);
	assert(state.numBuys == 1);
	assert(state.playedCardCount == 0);
	assert(state.whoseTurn == 0);
	assert(state.handCount[state.whoseTurn] == 5);	//5 card hand to start
	
	/****************************************************/
	numPlayer = 5;
	
	printf("Running unit test 2.3\n");
	printf("Running test with too many players. This will crash...\n");
	//running test 2.1 with 10 player count
	status = initializeGame(5, k, seed, &state);
	
	//bailing out if the game failed to initialize
	assert(status == 0);
	
	//checking number of players
	assert(state.numPlayers == numPlayer);
	
	//checking curse count
	assert(state.supplyCount[curse] = 10);
	
	//checking for correct supply counts
	for(i = 0; i < 10; i++){
		assert(state.supplyCount[i] == supplyCount);
	}
	
	//checking for decks size for player 1 (10 - 5) and player 2 (10)
	assert(state.deckCount[0] == (10 - 5));
	assert(state.deckCount[1] == 10);
	
	//checking discard pile
	assert(state.discardCount[i] == 0);
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		assert(state.embargoTokens[i] == 0);
    }
	
	//checking player 1 setup
	assert(state.outpostPlayed == 0);
	assert(state.phase == 0);
	assert(state.numActions == 1);
	assert(state.numBuys == 1);
	assert(state.playedCardCount == 0);
	assert(state.whoseTurn == 0);
	assert(state.handCount[state.whoseTurn] == 5);	//5 card hand to start

    printf("All tests passed!\n");

    return 0;
}