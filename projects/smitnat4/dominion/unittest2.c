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

/* this unit test will test the minion */
int main (int argc, char** argv)	{
	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	// declare the game state
	struct gameState G0, G1, G2, G3, G4;
	
	printf("----------------------------------\n");
	printf("Begin Testing minionCardEffect():\n");

	initializeGame(2, k, 999, &G0); // initialize a new game then copy it
	
	// start test 1 ----------------------------------------------------
	printf("unittest2 Test 1: Player chooses option 1 (gain 2 coins)\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t1choice1 = 1;
	int t1choice2 = 0;
	int t1player = 0;
	G1.hand[t1player][0] = minion;
	G1.hand[t1player][1] = smithy;
	G1.hand[t1player][2] = smithy;
	G1.hand[t1player][3] = smithy;
	G1.hand[t1player][4] = smithy;
	
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	minionCardEffect(&G2, t1choice1, t1choice2, 0 ,t1player); // call the refactored function with newly created G2
	customAssert(G2.coins, G1.coins+2);

	
	// end test 1 ------------------------------------------------------
	
	// start test 2 ----------------------------------------------------
	printf("unittest2 Test 2: Player chooses option 2(gains 4 cards)\n");
	int t2choice1 = 0;
	int t2choice2 = 1;
	int t2player = 0;
	memcpy(&G3, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	G3.hand[t2player][0] = minion;
	G3.hand[t2player][1] = smithy;
	G3.hand[t2player][2] = smithy;
	G3.hand[t2player][3] = smithy;
	G3.hand[t2player][4] = smithy;
	
	memcpy(&G4, &G3, sizeof(struct gameState)); // copy G1 to G2
	minionCardEffect(&G4, t2choice1, t2choice2, 0 ,t2player); // call the refactored function with newly game
	customAssert(G4.handCount[t2player], 4);
	// end test 2 ----------------------------------------------------

	// start test 3 ----------------------------------------------------
	printf("unittest2 Test 3: Player chooses option 2 and 2nd player has 5 cards (see if draws 4)\n");
	int t3choice1 = 0;
	int t3choice2 = 1;
	int t3player = 0;
	int t3playerOpponent = 1;
	memcpy(&G3, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	G3.hand[t2player][0] = minion;
	G3.hand[t2player][1] = smithy;
	G3.hand[t2player][2] = smithy;
	G3.hand[t2player][3] = smithy;
	G3.hand[t2player][4] = smithy;
	
	// setup opponent to have 5 cards
	G3.handCount[t3playerOpponent] = 5;
	G3.hand[t3playerOpponent][0] = smithy;
	G3.hand[t3playerOpponent][1] = smithy;
	G3.hand[t3playerOpponent][2] = smithy;
	G3.hand[t3playerOpponent][3] = smithy;
	G3.hand[t3playerOpponent][4] = smithy;
	
	memcpy(&G4, &G3, sizeof(struct gameState)); // copy G1 to G2
	minionCardEffect(&G4, t3choice1, t3choice2, 0 ,t3player); // call the refactored function with newly game
	customAssert(G4.handCount[t3playerOpponent], 4);
	// end test 3 ----------------------------------------------------
	
	printf("Test completed for minionCardEffect!\n");
	return 0;
}