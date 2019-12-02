#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

void customAssert(int a, int b){
    if(a == b){
        printf("Test passed!\n");
    }
    else{
        printf("Test failed!\n");
    }
}

/* this unit test will test the bug5 in scoreFor */
int main (int argc, char** argv)	{
	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	// declare the game state
	struct gameState G0, G1, G2;
	
	printf("----------------------------------\n");
	printf("Begin Testing bug#5:\n");

	initializeGame(2, k, 999, &G0); // initialize a new game then copy it
	
	// start test 1 ----------------------------------------------------
	printf("Test 1: Setup score so it should be 7 based on having a province and great_hall in deck. \n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int player = 0;
	G1.discardCount[player] = 0;
	G1.handCount[player] = 0;
	G1.deckCount[player] = 2;
	G1.deck[player][0] = province;
	G1.deck[player][1] = great_hall;
	int score = scoreFor(player,&G1); // call the refactored function with newly created G2
	printf("Score: %d\n",score);
	customAssert(score, 7);
	// end test 1 ------------------------------------------------------
	
	printf("Test completed for bug#5!\n");
	printf("----------------------------------\n");
	return 0;
}