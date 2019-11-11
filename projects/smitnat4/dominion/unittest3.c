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

/* this unit test will test the ambassador */
int main (int argc, char** argv)	{
	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	// declare the game state
	struct gameState G0, G1, G2;
	
	printf("----------------------------------\n");
	printf("Begin Testing ambassadorCardEffect():\n");

	initializeGame(2, k, 999, &G0); // initialize a new game then copy it
	
	// start test 1 ----------------------------------------------------
	printf("unittest3 Test 1: Player chooses to return 1 Smithy card (count should decrease by 1)\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t1choice1 = 1;
	int t1choice2 = 1;
	int t1player = 0;
	G1.hand[t1player][0] = ambassador;
	G1.hand[t1player][1] = smithy;
	G1.hand[t1player][2] = smithy;
	G1.hand[t1player][3] = smithy;
	G1.hand[t1player][4] = smithy;
	
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	ambassadorCardEffect(&G2, t1choice1, t1choice2, 0 ,t1player); // call the refactored function with newly created G2
	int G1SmithyCount = 0;
	for(int i = 0; i < G1.handCount[t1player]; i++){
        if (G1.hand[t1player][i] == smithy){
            G1SmithyCount++;
        }
    }
	int G2SmithyCount = 0;
	for(int i = 0; i < G2.handCount[t1player]; i++){
        if (G2.hand[t1player][i] == smithy){
            G2SmithyCount++;
        }
    }
	customAssert(G1SmithyCount, G1SmithyCount -1);
	// end test 1 ------------------------------------------------------
	
	// start test 2 ----------------------------------------------------
	printf("unittest3 Test 2: choice2 > 2 (function should return -1)\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t2choice1 = 1;
	int t2choice2 = 3;
	int t2player = 0;
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	int returnValue = ambassadorCardEffect(&G2, t2choice1, t2choice2, 0 ,t2player); // call the refactored function with newly created G2
	customAssert(returnValue, -1);

	// end test 2 ----------------------------------------------------

	// start test 3 ----------------------------------------------------
	printf("unittest3 Test 3: choice1 == handPos (function should return -1)\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t3choice1 = 0;
	int t3choice2 = 1;
	int t3player = 0;
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	int returnValue2 = ambassadorCardEffect(&G2, t3choice1, t3choice2, 0 ,t3player); // call the refactored function with newly created G2
	customAssert(returnValue2, -1);

	// end test 3 ----------------------------------------------------
	
	printf("Test completed for ambassadorCardEffect!\n");
	return 0;
}