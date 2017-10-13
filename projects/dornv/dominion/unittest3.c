/* -----------------------------------------------------------------------
 * Unit test for the buyCard() function within dominion.c
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
	
	struct gameState state;
	initializeGame(2, k, seed, &state);
	
	//int buyCard(int supplyPos, struct gameState *state)
	printf ("TESTING buyCard():\n");
	
	/****************************************************/
	printf("Running unit test 3.1\n");
	//decreasing the number of buys the current player has to 0
	state->numBuys--;
	int returnValue = buyCard(1, state);
	assert(returnValue == -1);
	initializeGame(2, k, seed, &state);
	
	/****************************************************/
	printf("Running unit test 3.2\n");
	//having a player buy a card without any coins
	state->coins = 0;
	returnValue = buyCard(1, state);
	assert(returnValue == -1);
	initializeGame(2, k, seed, &state);
	
	/****************************************************/
	printf("Running unit test 3.3\n");
	//test a supply count being set to zero then trying to buy it
	state->supplyCount[1] = 0;
	returnValue = buyCard(1, state);
	assert(returnValue == -1);
	initializeGame(2, k, seed, &state);
	
	/****************************************************/
	printf("Running unit test 3.4\n");
	//setting up the player to have lots of money and a buy
	state->coins = 10;
	struct gameState temp;	//temp struct for the state
	memcpy(temp, state, sizeof(struct gameState));
	returnValue = buyCard(1, state);
	assert(returnValue == 0);
	assert(state->numBuys == temp->numBuys--);
	assert(state->coins == (state->coins) - (getCost(1)));
	
	printf("All tests passed!\n");

    return 0;
}