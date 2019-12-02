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

/* this unit test will test the bug1 in mine */
int main (int argc, char** argv)	{
	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	// declare the game state
	struct gameState G0, G1, G2;
	
	printf("----------------------------------\n");
	printf("Begin Testing bug#1():\n");

	initializeGame(2, k, 999, &G0); // initialize a new game then copy it
	
	// start test 2 ----------------------------------------------------
	printf("Test: Player chooses a valid card(assert played card count only increases by 1 (not 2))\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t2choice1 = 1;
	int t2choice2 = silver;
	int t2player = 0;
	G1.hand[t2player][0] = mine;
	G1.hand[t2player][1] = copper;
	G1.hand[t2player][2] = smithy;
	G1.hand[t2player][3] = smithy;
	G1.hand[t2player][4] = smithy;
	
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	mineCardEffect(&G2,t2player, t2choice1, t2choice2, 0); // call the refactored function with newly created G2
	int playedCountBefore = G1.playedCardCount;
	int playedCountAfter = G2.playedCardCount;
	printf("Count before: %d\n",playedCountBefore);
	printf("Count after: %d\n",playedCountAfter);
	customAssert(playedCountBefore+1, playedCountAfter);
	// end test 2 ------------------------------------------------------
	
	printf("Test completed for bug#1!\n");
	printf("----------------------------------\n");
	return 0;
}