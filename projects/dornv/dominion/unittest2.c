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
	int passed = 0;
	int testPassed = 0;
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
	printf("Running unit test 2.1: Testing InitializeGame with 2 Player Game\n");
	int status = initializeGame(2, k, seed, &state);
	
	//bailing out if the game failed to initialize
	//assert(status == 0);
	if(status != 0){
		//failing test if status != 0
		printf("Status: %d; Expected: 0\n", status);
		passed = 1;
	}
	
	//checking number of players
	//assert(state.numPlayers == numPlayer);
	if(state.numPlayers != numPlayer){
		//failing test if num players is incorrect
		printf("NumPlayers: %d; Expected: %d\n", state.numPlayers, numPlayer);
		passed = 1;
	}
	
	//checking curse count
	//assert(state.supplyCount[curse] = 10);
	if(state.supplyCount[curse] != 10){
		//failing test if curse count is incorrect
		printf("Curse Count: %d; Expected: %d\n", state.supplyCount[curse], 10);
		passed = 1;
	}
	
	//checking for correct supply counts
	for(i = 0; i < 10; i++){
		if(i == 9 || i == 6){
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			assert(state.supplyCount[k[i]] == victoryCount);
			if(state.supplyCount[k[i]] != victoryCount){
				//failing test if victory card count is incorrect
				printf("VictoryCount[%d][%d]: %d; Expected: %d\n", k, i, state.supplyCount[k[i]], victoryCount);
				passed = 1;
			}
		}
		else{
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			assert(state.supplyCount[k[i]] == supplyCount);
			if(state.supplyCount[k[i]] != supplyCount){
				//failing test if supply card count is incorrect
				printf("SupplyCount[%d][%d]: %d; Expected: %d\n", k, i, state.supplyCount[k[i]], supplyCount);
				passed = 1;
			}
		}
	}
	
	//checking for decks size for player 1 (10 - 5) and player 2 (10)
	//assert(state.deckCount[0] == (10 - 5));
	if(state.deckCount[0] != (10 - 5)){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[0], 5);
		passed = 1;
	}
	
	//assert(state.deckCount[1] == 10);
	if(state.deckCount[1] != 10){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[1], 10);
		passed = 1;
	}
	
	//checking discard pile
	//assert(state.discardCount[0] == 0);
	if(state.discardCount[0] != 0){
		//failing test if discardCount P1 is incorrect
		printf("Discard Pile P1: %d; Expected: %d\n", state.discardCount[0], 0);
		passed = 1;
	}
	
	if(state.discardCount[1] != 0){
		//failing test if discardCount P1 is incorrect
		printf("Discard Pile P1: %d; Expected: %d\n", state.discardCount[1], 0);
		passed = 1;
	}
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		//assert(state.embargoTokens[i] == 0);
		if(state.embargoTokens[i] != 0){
			//failing test if embargo token count is incorrect
			printf("Embargo Tokens: %d; Expected: %d\n", state.embargoTokens[i], 0);
			passed = 1;
		}
    }
	
	//checking player 1 setup
	//assert(state.outpostPlayed == 0);
	if(state.outpostPlayed != 0){
		//failing test if outpost played is incorrect
		printf("Outpost Played: %d; Expected: %d\n", state.outpostPlayed, 0);
		passed = 1;
	}
	
	//assert(state.phase == 0);
	if(state.phase != 0){
		//failing test if phase is incorrect
		printf("Phase: %d; Expected: %d\n", state.phase, 0);
		passed = 1;
	}
	
	//assert(state.numActions == 1);
	if(state.numActions != 1){
		//failing test if num actions is incorrect
		printf("NumActions: %d; Expected: %d\n", state.numActions, 1);
		passed = 1;
	}
	
	//assert(state.numBuys == 1);
	if(state.numBuys != 1){
		//failing test if num buys is incorrect
		printf("NumBuys: %d; Expected: %d\n", state.numBuys, 1);
		passed = 1;
	}
	
	//assert(state.playedCardCount == 0);
	if(state.playedCardCount != 0){
		//failing test if played card count is incorrect
		printf("PlayedCardCount: %d; Expected: %d\n", state.playedCardCount, 0);
		passed = 1;
	}
	
	//assert(state.whoseTurn == 0);
	if(state.whoseTurn != 0){
		//failing test if turn is incorrect
		printf("WhoseTurn: %d; Expected: %d\n", state.whoseTurn, 0);
		passed = 1;
	}
	
	//assert(state.handCount[state.whoseTurn] == 5);	//5 card hand to start
	if(state.handCount[state.whoseTurn] != 5){
		//failing test if turn is incorrect
		printf("P1 Handcount: %d; Expected: %d\n", state.handCount[state.whoseTurn], 5);
		passed = 1;
	}
	
	//passing tests if all checks passed
	if(passed == 0){
		testPassed++;
	}
	
	/****************************************************/
	//setting up values for 4 player game
	//supplyCount = 10;
	provienceCount = 12;
	victoryCount = 12;
	numPlayer = 4;
	passed = 0;
	
	printf("Running unit test 2.2: Testing InitializeGame with 4 Player Game\n");
	//running test 2.1 with 4 player count
	status = initializeGame(4, k, seed, &state);
	
	//bailing out if the game failed to initialize
	//assert(status == 0);
	if(status != 0){
		//failing test if status != 0
		printf("Status: %d; Expected: 0\n", status);
		passed = 1;
	}
	
	//checking number of players
	//assert(state.numPlayers == numPlayer);
	if(state.numPlayers != numPlayer){
		//failing test if num players is incorrect
		printf("NumPlayers: %d; Expected: %d\n", state.numPlayers, numPlayer);
		passed = 1;
	}
	
	//checking curse count
	//assert(state.supplyCount[curse] = 30);
	if(state.supplyCount[curse] != 30){
		//failing test if curse count is incorrect
		printf("Curse Count: %d; Expected: %d\n", state.supplyCount[curse], 30);
		passed = 1;
	}
	
	//checking for correct supply counts
	for(i = 0; i < 10; i++){
		if(i == 9 || i == 6){
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			//assert(state.supplyCount[k[i]] == victoryCount);
			if(state.supplyCount[k[i]] != victoryCount){
				//failing test if victory card count is incorrect
				printf("VictoryCount[%d][%d]: %d; Expected: %d\n", k, i, state.supplyCount[k[i]], victoryCount);
				passed = 1;
			}
		}
		else{
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			//assert(state.supplyCount[k[i]] == supplyCount);
			if(state.supplyCount[k[i]] != supplyCount){
				//failing test if supply card count is incorrect
				printf("SupplyCount[%d][%d]: %d; Expected: %d\n", k, i, state.supplyCount[k[i]], supplyCount);
				passed = 1;
			}
		}
	}
	
	//checking for decks size for player 1 (10 - 5) and player 2 and player 3 and player 4 (10)
	//assert(state.deckCount[0] == (10 - 5));
	if(state.deckCount[0] != (10 - 5)){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[0], 5);
		passed = 1;
	}
	
	//assert(state.deckCount[1] == 10);
	if(state.deckCount[1] != 10){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[1], 10);
		passed = 1;
	}
	
	//assert(state.deckCount[1] == 10);
	if(state.deckCount[2] != 10){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[2], 10);
		passed = 1;
	}
	
	//assert(state.deckCount[1] == 10);
	if(state.deckCount[3] != 10){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[3], 10);
		passed = 1;
	}
	
	//checking discard pile
	//assert(state.discardCount[0] == 0);
	if(state.discardCount[0] != 0){
		//failing test if discardCount P1 is incorrect
		printf("Discard Pile P1: %d; Expected: %d\n", state.discardCount[0], 0);
		passed = 1;
	}
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		//assert(state.embargoTokens[i] == 0);
		if(state.embargoTokens[i] != 0){
			//failing test if embargo token count is incorrect
			printf("Embargo Tokens: %d; Expected: %d\n", state.embargoTokens[i], 0);
			passed = 1;
		}
    }
	
	//checking player 1 setup
	//assert(state.outpostPlayed == 0);
	if(state.outpostPlayed != 0){
		//failing test if outpost played is incorrect
		printf("Outpost Played: %d; Expected: %d\n", state.outpostPlayed, 0);
		passed = 1;
	}
	
	//assert(state.phase == 0);
	if(state.phase != 0){
		//failing test if phase is incorrect
		printf("Phase: %d; Expected: %d\n", state.phase, 0);
		passed = 1;
	}
	
	//assert(state.numActions == 1);
	if(state.numActions != 1){
		//failing test if num actions is incorrect
		printf("NumActions: %d; Expected: %d\n", state.numActions, 1);
		passed = 1;
	}
	
	//assert(state.numBuys == 1);
	if(state.numBuys != 1){
		//failing test if num buys is incorrect
		printf("NumBuys: %d; Expected: %d\n", state.numBuys, 1);
		passed = 1;
	}
	
	//assert(state.playedCardCount == 0);
	if(state.playedCardCount != 0){
		//failing test if played card count is incorrect
		printf("PlayedCardCount: %d; Expected: %d\n", state.playedCardCount, 0);
		passed = 1;
	}
	
	//assert(state.whoseTurn == 0);
	if(state.whoseTurn != 0){
		//failing test if turn is incorrect
		printf("WhoseTurn: %d; Expected: %d\n", state.whoseTurn, 0);
		passed = 1;
	}
	
	//assert(state.handCount[state.whoseTurn] == 5);	//5 card hand to start
	if(state.handCount[state.whoseTurn] != 5){
		//failing test if turn is incorrect
		printf("P1 Handcount: %d; Expected: %d\n", state.handCount[state.whoseTurn], 5);
		passed = 1;
	}
	
	//passing tests if all checks passed
	if(passed == 0){
		testPassed++;
	}
	
	/****************************************************/
	numPlayer = 3;
	passed = 0;
	
	printf("Running unit test 2.3: Testing InitializeGame with 3 Player Game\n");
	//running test 2.1 with 10 player count
	status = initializeGame(3, k, seed, &state);
	
	//bailing out if the game failed to initialize
	//assert(status == 0);
	if(status != 0){
		//failing test if status != 0
		printf("Status: %d; Expected: 0\n", status);
		passed = 1;
	}
	
	//checking number of players
	//assert(state.numPlayers == numPlayer);
	if(state.numPlayers != numPlayer){
		//failing test if num players is incorrect
		printf("NumPlayers: %d; Expected: %d\n", state.numPlayers, numPlayer);
		passed = 1;
	}
	
	//checking curse count
	assert(state.supplyCount[curse] = 10);
	if(state.supplyCount[curse] != 10){
		//failing test if curse count is incorrect
		printf("Curse Count: %d; Expected: %d\n", state.supplyCount[curse], 10);
		passed = 1;
	}
	
	//checking for correct supply counts
	for(i = 0; i < 10; i++){
		if(i == 9 || i == 6){
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			//assert(state.supplyCount[k[i]] == victoryCount);
			if(state.supplyCount[k[i]] != victoryCount){
				//failing test if victory card count is incorrect
				printf("VictoryCount[%d][%d]: %d; Expected: %d\n", k, i, state.supplyCount[k[i]], victoryCount);
				passed = 1;
			}
		}
		else{
			//printf("Supply count for item %d: %d\n", i, state.supplyCount[k[i]]);
			//assert(state.supplyCount[k[i]] == supplyCount);
			if(state.supplyCount[k[i]] != supplyCount){
				//failing test if supply card count is incorrect
				printf("SupplyCount[%d][%d]: %d; Expected: %d\n", k, i, state.supplyCount[k[i]], supplyCount);
				passed = 1;
			}
		}
	}
	
	//checking for decks size for player 1 (10 - 5) and player 2 and 3 (10)
	//assert(state.deckCount[0] == (10 - 5));
	if(state.deckCount[0] != (10 - 5)){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[0], 5);
		passed = 1;
	}
	
	//assert(state.deckCount[1] == 10);
	if(state.deckCount[1] != 10){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[1], 10);
		passed = 1;
	}
	
	//assert(state.deckCount[2] == 10);
	if(state.deckCount[2] != 10){
		//failing test if deckCount P1 is incorrect
		printf("Deck Count P1: %d; Expected: %d\n", state.deckCount[2], 10);
		passed = 1;
	}
	
	//checking discard pile
	//assert(state.discardCount[0] == 0);
	if(state.discardCount[0] != 0){
		//failing test if discardCount P1 is incorrect
		printf("Discard Pile P1: %d; Expected: %d\n", state.discardCount[0], 0);
		passed = 1;
	}
	
	//checking embargo tokens count(s)
	for (i = 0; i <= treasure_map; i++){
		//assert(state.embargoTokens[i] == 0);
		if(state.embargoTokens[i] != 0){
			//failing test if embargo token count is incorrect
			printf("Embargo Tokens: %d; Expected: %d\n", state.embargoTokens[i], 0);
			passed = 1;
		}
    }
	
	//checking player 1 setup
	//assert(state.outpostPlayed == 0);
	if(state.outpostPlayed != 0){
		//failing test if outpost played is incorrect
		printf("Outpost Played: %d; Expected: %d\n", state.outpostPlayed, 0);
		passed = 1;
	}
	
	//assert(state.phase == 0);
	if(state.phase != 0){
		//failing test if phase is incorrect
		printf("Phase: %d; Expected: %d\n", state.phase, 0);
		passed = 1;
	}
	
	//assert(state.numActions == 1);
	if(state.numActions != 1){
		//failing test if num actions is incorrect
		printf("NumActions: %d; Expected: %d\n", state.numActions, 1);
		passed = 1;
	}
	
	//assert(state.numBuys == 1);
	if(state.numBuys != 1){
		//failing test if num buys is incorrect
		printf("NumBuys: %d; Expected: %d\n", state.numBuys, 1);
		passed = 1;
	}
	
	//assert(state.playedCardCount == 0);
	if(state.playedCardCount != 0){
		//failing test if played card count is incorrect
		printf("PlayedCardCount: %d; Expected: %d\n", state.playedCardCount, 0);
		passed = 1;
	}
	
	//assert(state.whoseTurn == 0);
	if(state.whoseTurn != 0){
		//failing test if turn is incorrect
		printf("WhoseTurn: %d; Expected: %d\n", state.whoseTurn, 0);
		passed = 1;
	}
	
	//assert(state.handCount[state.whoseTurn] == 5);	//5 card hand to start
	if(state.handCount[state.whoseTurn] != 5){
		//failing test if turn is incorrect
		printf("P1 Handcount: %d; Expected: %d\n", state.handCount[state.whoseTurn], 5);
		passed = 1;
	}
	
	//passing tests if all checks passed
	if(passed == 0){
		testPassed++;
	}

    printf("Passing Tests: %d/3\n", testPassed);

    return 0;
}