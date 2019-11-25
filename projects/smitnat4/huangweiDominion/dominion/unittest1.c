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

/* this unit test will test the baron */
int main (int argc, char** argv)	{
	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	// declare the game state
	struct gameState G0, G1, G2, G3, G4, G5, G6;
	printf("----------------------------------\n");
	printf("Begin Testing baronaction():\n");
	
	initializeGame(2, k, 999, &G0); // initialize a new game then copy it
	
	// start test 1 ----------------------------------------------------
	printf("unittest1 Test 1: Player discards estate card and has one\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t1choice1 = 1;
	int t1player = 0;
	G1.hand[t1player][0] = baron;
	G1.hand[t1player][1] = estate;
	G1.hand[t1player][2] = smithy;
	G1.hand[t1player][3] = smithy;
	G1.hand[t1player][4] = smithy;
	
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	baronaction(t1choice1,&G2, t1player); // call the refactored function with newly created G2
	
	G1.coins += 4; // add 4 coins
	G1.handCount[t1player]--; // reduce handcount by 1
	
	
	customAssert(G1.coins, G2.coins);
	customAssert(G1.handCount[t1player], G2.handCount[t1player]);

	
	// end test 1 ------------------------------------------------------
	
	// start test 2 ----------------------------------------------------
	printf("unittest1 Test 2: Player discards estate card but doesn't have one\n");
	memcpy(&G3, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t2choice1 = 1;
	int t2player = 0;
	G3.hand[t2player][0] = baron;
	G3.hand[t2player][1] = smithy;
	G3.hand[t2player][2] = smithy;
	G3.hand[t2player][3] = smithy;
	G3.hand[t2player][4] = smithy;
	
	memcpy(&G4, &G3, sizeof(struct gameState)); // copy G3 to G4
	baronaction(t2choice1,&G4, t1player); // call the refactored function with newly created G2
	
	customAssert(G3.handCount[t2player],G4.handCount[t2player]);
	// end test 2 ------------------------------------------------------
	
	// start test 3 ----------------------------------------------------
	printf("unittest1 Test 3: Ensure game ends if all estate cards are discarded\n");
	memcpy(&G5, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t3choice1 = 0;
	int t3player = 0;
	G5.hand[t3player][0] = baron;
	G5.hand[t3player][1] = estate;
	G5.hand[t3player][2] = smithy;
	G5.hand[t3player][3] = smithy;
	G5.hand[t3player][4] = smithy;
	G5.supplyCount[estate] = 1;
	
	memcpy(&G6, &G5, sizeof(struct gameState)); // copy G5 to G6
	baronaction(t3choice1,&G6, t3player); // call the refactored function with newly created G6
	
	// ensure estate discarded and game is over
	int g6Estates = G6.supplyCount[estate];//supplyCount(estate, G6);
	customAssert(g6Estates, 0);
	// end test 3 ------------------------------------------------------
	
	printf("Test completed for baronaction!\n");
	
	return 0;
}