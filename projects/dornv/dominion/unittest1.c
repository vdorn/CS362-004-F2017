/* -----------------------------------------------------------------------
 * Unit test for the isGameOver() function within dominion.c
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	struct gameState state;
	
	//cards to be used in this "game"
	int k[10] = {adventurer, village, mine, smithy, council_room, feast, gardens, remodel, baron, great_hall};
		   
	int seed = 1000;	//some random seed to initialize game

	initializeGame(2, k, seed), &G);

	int i=0;
	
	srand(time(NULL));

    printf ("TESTING isGameOver():\n");

	//testing that a game is over if providences is 0 or if 3 supply piles are zero
	
	//testing 11 values to provience counts
	//there are only 8 providence in a 2 player game
	//all values from 0-8 are tested along with a few outliers and a repeated 0
	int testValues[11] = [0, 1, 2, 3, 4, 5, 6, 7, 8, -1, 0, 10];
	
	/****************************************************/
	printf("Running unit test 1.1\n");
	for(int i = 0; i < 12; i++){
		//adding -1, 1 or 0 to the province count
		state->supplyCount[province] = testValues[i];
		
		printf("Provience Count: %d\n", state->supplyCount[province]);
		
		int value = isGameOver();
		if (state->supplyCount[province] == 0){
			assert(value == 0);
			printf("Test 1 passed with provience count: %d\n", testValues[i]);
		}
	}
	
	/****************************************************/
	printf("Running unit test 1.2\n");
	//supply testing with 4 kingdom cards
	//there are only 8 of each supply for 2 players
	for(i = 0; i < 11; i++){
		for(int j = 0; j < 10; j++){
			state->supplyCount[j] = testValues[i]
		}
		
		int value = isGameOver();
		
		//testing to see if isGameOver should return 0
		int m;
		for (i = 0; i < 10; i++){
			if (state->supplyCount[i] == 0){
				//if a supplyCount is 0 increment m which is a counter for supplyCounts that equal 0
				m++;
			}
		}
		
		if (m >= 3){
			assert(value == 0);
			printf("Test 2 passed with 3 supply counts equaling zero\n", testValues[i]);
		}
	}
	
	/****************************************************/
	printf("Running unit test 1.3\n");
	//testing random combinations for testValues with supplys 1000 times
	for(i = 0; i < 1000; i++){
		for(int j = 0; j < 10; j++){
			state->supplyCount[j] = testValues[rand() % 11]
		}
		
		int value = isGameOver();
		
		//testing to see if isGameOver should return 0
		int m;
		for (i = 0; i < 4; i++){
			if (state->supplyCount[i] == 0){
				//if a supplyCount is 0 increment m which is a counter for supplyCounts that equal 0
				m++;
			}
		}
		
		if (m == 3){
			assert(value == 0);
			printf("Test 3 passed with 3 supply counts equaling zero\n", testValues[i]);
		}
	}

    printf("All tests passed!\n");

    return 0;
}