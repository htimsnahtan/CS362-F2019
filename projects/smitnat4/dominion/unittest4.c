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

/* this unit test will test the tribute */
int main (int argc, char** argv)	{
	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	// declare the game state
	struct gameState G0, G1, G2;
	
	printf("----------------------------------\n");
	printf("Begin Testing tributeCardEffect():\n");

	initializeGame(2, k, 999, &G0); // initialize a new game then copy it
	
	// start test 1 ----------------------------------------------------
	printf("unittest4 Test 1: Opponent has no cards in discard or deck (assert no changes to their deck)\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t1player = 0;
	int t1player2 = 1;
	int tributeRevealedCards[2] = {-1,-1};
	G1.hand[t1player][0] = tribute;
	G1.hand[t1player][1] = smithy;
	G1.hand[t1player][2] = smithy;
	G1.hand[t1player][3] = smithy;
	G1.hand[t1player][4] = smithy;
	
	// opponent has no cards in deck or discard
	G1.deckCount[t1player2] = 0;
	G1.discardCount[t1player2] = 0;
	
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	tributeCardEffect(&G2, t1player2, t1player,tributeRevealedCards); // call the refactored function with newly created G2
	customAssert(G1.deckCount[t1player2], G2.deckCount[t1player2]);
	// end test 1 ------------------------------------------------------
	
	// start test 2 ----------------------------------------------------
	printf("unittest4 Test 2: Reveal a treasure card and action card (assert player should gain 2 gold then assert they gain 2 actions)\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t2player = 0;
	int t2player2 = 1;
	int t2tributeRevealedCards[2] = {tribute,silver};
	G1.hand[t2player][0] = tribute;
	G1.hand[t2player][1] = smithy;
	G1.hand[t2player][2] = smithy;
	G1.hand[t2player][3] = smithy;
	G1.hand[t2player][4] = smithy;
	
	// opponent has no tribute and silver
	G1.deckCount[t1player2] = 2;
	G1.deck[t2player2][0] = tribute;
	G1.deck[t2player2][1] = silver;
	
	
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	tributeCardEffect(&G2, t2player2, t2player,t2tributeRevealedCards); // call the refactored function with newly created G2
	
	// assert coins +2
	customAssert(G1.coins+2, G2.coins);
	// assert actions +2
	customAssert(G1.numActions+2, G2.numActions);

	// end test 2 ------------------------------------------------------
	
	// start test 3 ----------------------------------------------------
	printf("unittest4 Test 3: Reveal a victory card (assert cards +2 for player)\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t3player = 0;
	int t3player2 = 1;
	int t3tributeRevealedCards[2] = {estate,-1};
	G1.hand[t3player][0] = tribute;
	G1.hand[t3player][1] = smithy;
	G1.hand[t3player][2] = smithy;
	G1.hand[t3player][3] = smithy;
	G1.hand[t3player][4] = smithy;
	
	// opponent has only estate
	G1.deckCount[t1player2] = 1;
	G1.deck[t3player2][0] = estate;
	
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	tributeCardEffect(&G2, t3player2, t3player,t3tributeRevealedCards); // call the refactored function with newly created G2
	customAssert(G1.handCount[t3player], G2.handCount[t3player] -2);
	// end test 3 ----------------------------------------------------

	// start test 4 ----------------------------------------------------
	printf("unittest4 Test 4: Opponent has no cards in discard\n");
	memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
	int t4player = 0;
	int t4player2 = 1;
	int t4tributeRevealedCards[2] = {-1,-1};
	G1.hand[t4player][0] = tribute;
	G1.hand[t4player][1] = smithy;
	G1.hand[t4player][2] = smithy;
	G1.hand[t4player][3] = smithy;
	G1.hand[t4player][4] = smithy;
	
	// opponent has no cards in deck or discard
	G1.deckCount[t4player2] = 0;
	G1.discardCount[t4player2] = 1;
	G1.discard[t4player2][0] = gold;
	
	memcpy(&G2, &G1, sizeof(struct gameState)); // copy G1 to G2
	tributeCardEffect(&G2, t4player2, t1player,t4tributeRevealedCards); // call the refactored function with newly created G2
	customAssert(G1.deckCount[t4player2], G2.deckCount[t4player2]);
	// end test 4 ------------------------------------------------------
	
	printf("Test completed for tributeCardEffect!\n");
	return 0;
}