#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h>

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
	printf("----------------------------------\n");
	printf("Begin random testing for minion card\n");
	// do the testing
	
	// to prevent sequence repetition between runs    
	srand(time(NULL));
	
	// set the card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	
	// setup random seed
	int seed = rand() % 100;
	
	// declare the game states
	struct gameState G0, G1, G2;
	
	// setup number of players
	int numberOfPlayers = rand() % (MAX_PLAYERS + 1 - 2) + 2;
	
	// init game
	int initGameReturnValue = initializeGame(numberOfPlayers, k, seed, &G0);
	
	// verify game was setup properly
	printf("Test game was setup properly: ");
	customAssert(initGameReturnValue, 0);
	
	
	int test1Run = 0; // Player chooses option 1 (gain 2 coins)
	int test2Run = 0; // Player chooses option 2(gains 4 cards)
	int test3Run = 0; // Player chooses option 2 and 2nd player has 5 cards (see if draws 4)
	int numberOfTestsRun = 0;
	
	while (!test1Run || !test2Run || !test3Run) {
		numberOfTestsRun++;
		printf("Running test %d\n",numberOfTestsRun);
		
		// copy G0 to G1 so that we don't mutate G1 (which is the initial game state)
		memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
		
		int t1HandCount = rand() % (MAX_HAND + 1 - 0) + 0;
		int t1HandCountPlayer2 = rand() % (MAX_HAND + 1 - 0) + 0;
		int t1choice1 = rand() % (1 + 1 - 0) + 0; // boolean
		int t1choice2 = rand() % (1 + 1 - 0) + 0; // boolean
		int t1Player = rand() % numberOfPlayers;
		int t1Player2 = rand() % numberOfPlayers;
		while (t1Player == t1Player2) { // make sure player 1 and 2 aren't the same
			t1Player2 = rand() % numberOfPlayers;
		}
		G1.whoseTurn = t1Player;
		G1.handCount[t1Player] = t1HandCount;
		
		// setup a random hand for player
		for (int i = 0; i < t1HandCount; i++) {
			int randomCard = rand() % (treasure_map + 1); // treasure map is the last card enum
			G1.hand[t1Player][i] = randomCard;
		}
		
		// setup a random hand for player 2
		for (int i = 0; i < t1HandCountPlayer2; i++) {
			int randomCard = rand() % (treasure_map + 1); // treasure map is the last card enum
			G1.hand[t1Player2][i] = randomCard;
		}
		
		memcpy(&G2, &G1, sizeof(struct gameState));
		minionaction(t1choice1,&G2, 0,t1Player,t1choice2);
		
		if (t1choice1 && !t1choice2) { //Player chooses option 1 (gain 2 coins)
			printf("Running test for player choosing option 1(gain 2 coins)\n");
			test1Run = 1;
			customAssert(G2.coins, G1.coins+2);
		}
		if (!t1choice1 && t1choice2) { // Player chooses option 2(gains 4 cards)
			test2Run = 1;
			printf("Running test for player choosing option 2(gain 4 cards)\n");
			customAssert(G2.handCount[t1Player], 4);
		}
		if (t1HandCountPlayer2 >= 5 && t1choice2) {
			test3Run = 1;
			printf("Running test for player chooses option 2 and 2nd player has 5 cards (see if draws 4)\n");
			customAssert(G2.handCount[t1Player2], 4);
		}

	
	}
	
	
	
	printf("Finished random testing for minion card\n");
	printf("----------------------------------\n");
	return 0;
}