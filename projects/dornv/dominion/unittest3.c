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
    int seed = 37;
    int numPlayer = 2;
	int k[10] = {adventurer, village, mine, smithy, council_room, feast, gardens, remodel, baron, great_hall};
	int testPassed = 0;
	int passed = 0;
	
	struct gameState state;
	
	//int buyCard(int supplyPos, struct gameState *state)
	printf ("TESTING buyCard():\n");
	
	/****************************************************/
	printf("Running unit test 3.1: Testing Buy Card on a Player with No Buys\n");
	initializeGame(2, k, seed, &state);
	//decreasing the number of buys the current player has to 0
	state.numBuys--;
	int returnValue = buyCard(1, &state);
	//assert(returnValue == -1);
	if(returnValue == -1){
		testPassed++;
	}
	else{
		printf("Buy card returned: %d, Expected: %d\n", returnValue, -1);
	}
	
	/****************************************************/
	printf("Running unit test 3.2: Testing Buy Card on a Player without Any Coins\n");
	initializeGame(2, k, seed, &state);
	//having a player buy a card without any coins
	state.coins = 0;
	returnValue = buyCard(1, &state);
	//assert(returnValue == -1);
	if(returnValue == -1){
		testPassed++;
	}
	else{
		printf("Buy card returned: %d, Expected: %d\n", returnValue, -1);
	}
	
	/****************************************************/
	printf("Running unit test 3.3: Testing Buying a Card that isn't there\n");
	initializeGame(2, k, seed, &state);
	//test a supply count being set to zero then trying to buy it
	state.supplyCount[1] = 0;
	returnValue = buyCard(1, &state);
	//assert(returnValue == -1);
	if(returnValue == -1){
		testPassed++;
	}
	else{
		printf("Buy card returned: %d, Expected: %d\n", returnValue, -1);
	}
	
	/****************************************************/
	printf("Running unit test 3.4: Testing Buying a Card with Enough Money to Buy Said Card\n");
	initializeGame(2, k, seed, &state);
	//setting up the player to have lots of money and a buy
	state.coins = 10;
	struct gameState temp;	//temp struct for the state
	memcpy(&temp, &state, sizeof(struct gameState));
	returnValue = buyCard(1, &state);
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Buy card returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.numBuys == temp.numBuys - 1);
	if(state.numBuys != (temp.numBuys - 1)){
		passed = 1;
		printf("Num buys: %d, Expected: %d\n", state.numBuys, temp.numBuys - 1);
	}

	
	//assert(state.coins == (10 - getCost(1)));
	if(state.coins != (10 - getCost(1))){
		passed = 1;
		printf("Coins: %d, Expected: %d\n", state.coins, (10 - getCost(1)));
	}

	
	if(passed == 0){
		testPassed++;
	}
	
	printf("Passing Tests: %d/4\n", testPassed);

    return 0;
}