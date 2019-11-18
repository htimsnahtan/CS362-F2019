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

/* this unit test will test the baron */
int main (int argc, char** argv)	{
	printf("----------------------------------\n");
	printf("Begin random testing for baron card\n");
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
	
	
	int test1Run = 0;// has estate and is wanting to discard it
	int test2Run = 0;// doesn't have estate and wants to discard it
	int test3Run = 0;// doesn't want to discard estate
	int numberOfTestsRun = 0;
	
	while (!test1Run || !test2Run || !test3Run) {
		numberOfTestsRun++;
		printf("Running test %d\n",numberOfTestsRun);
		
		// copy G0 to G1 so that we don't mutate G1 (which is the initial game state)
		memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
		
		int t1HandCount = rand() % (MAX_HAND + 1 - 0) + 0;
		int t1choice1 = rand() % (1 + 1 - 0) + 0; // boolean where 1 means player is wanting to discard an estate
		int t1Player = rand() % numberOfPlayers;
		int t1HasEstate = 0;
		int t1SupplyCountOneLeft = rand() % (1 + 1 - 0) + 0;
		G1.whoseTurn = t1Player;
		G1.handCount[t1Player] = t1HandCount;
		
		// setup a random hand for player
		for (int i = 0; i < t1HandCount; i++) {
			int randomCard = rand() % (treasure_map + 1); // treasure map is the last card enum
			if (randomCard == estate) {
				t1HasEstate = 1;
			}
			G1.hand[t1Player][i] = randomCard;
		}

		if (!t1choice1) { // doesn't want to discard estate
			if (t1SupplyCountOneLeft) { // 50% chance game should be ended
				G2.supplyCount[estate] = 1;
			}
		}
		
		memcpy(&G2, &G1, sizeof(struct gameState));
		baronCardEffect(&G2, t1choice1, t1Player);
		
		if (t1HasEstate && t1choice1) { // has estate and is wanting to discard it
			test1Run = 1;
			G1.coins += 4; // add 4 coins
			G1.handCount[t1Player]--; // reduce handcount by 1
			printf("Player has estate and wants to discard it test case:\n");
			customAssert(G1.coins, G2.coins);
			customAssert(G1.handCount[t1Player], G2.handCount[t1Player]);
		}
		if (!t1HasEstate && t1choice1) { // doesn't have estate and wants to discard it
			test2Run = 1;
			printf("Player doesn't estate and wants to discard it test case:\n");
			customAssert(G1.handCount[t1Player],G2.handCount[t1Player]);
		}
		if (!t1choice1) { // doesn't want to discard estate
			if (t1SupplyCountOneLeft) { // 50% chance game should be ended
				test3Run = 1;
				printf("Only 1 estate is left. Testing if game is over\n");
				customAssert(G2.supplyCount[estate], 0);
			}
		}
	
	}
	
	
	
	printf("Finished random testing for baron card\n");
	printf("----------------------------------\n");
	return 0;
}