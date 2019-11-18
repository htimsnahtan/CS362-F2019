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

/* this unit test will test the tribute */
int main (int argc, char** argv)	{
	printf("----------------------------------\n");
	printf("Begin random testing for tribute card\n");
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
	
	
	int test1Run = 0; // Opponent has no cards in discard or deck (assert no changes to their deck)
	int test2Run = 0; // Reveal a treasure card and action card (assert player should gain 2 gold then assert they gain 2 actions)
	int test3Run = 0; // Reveal a victory card (assert cards +2 for player)
	int test4Run = 0; // Opponent has no cards in discard
	int numberOfTestsRun = 0;
	
	while (!test1Run || !test2Run || !test3Run || !test4Run) {
		numberOfTestsRun++;
		printf("Running test %d\n",numberOfTestsRun);
		
		// copy G0 to G1 so that we don't mutate G1 (which is the initial game state)
		memcpy(&G1, &G0, sizeof(struct gameState)); // G0 will never change and everything else will be copied from it
		
		//int randomNumber1to10 = rand() % 10;
		int t1HandCount = rand() % (MAX_HAND + 1 - 0) + 0;
		int t1HandCountPlayer2 = rand() % (MAX_HAND + 1 - 0) + 0;
		int t1Player = rand() % numberOfPlayers;
		int t1Player2 = rand() % numberOfPlayers;
		int t1Player2DiscardCount = rand() % (10 + 0 - 0) + 0;
		int t1Player2DeckCount = rand() % (10 + 0 - 0) + 0;
		int revealedCard1 = rand() % treasure_map;
		int revealedCard2 = rand() % treasure_map;
		int tributeRevealedCards[2] = {-1,-1};
		int hasTreasureCard = 0;
		int hasActionCard = 0;
		int hasEstateCard = 0;
		while (t1Player == t1Player2) { // make sure player 1 and 2 aren't the same
			t1Player2 = rand() % numberOfPlayers;
		}
		G1.whoseTurn = t1Player;
		G1.handCount[t1Player] = t1HandCount;
		
		// setup a random hand for player
		for (int i = 0; i < t1HandCount; i++) {
			int randomCard = rand() % (treasure_map); // treasure map is the last card enum
			G1.hand[t1Player][i] = randomCard;
		}
		
		// setup a random hand for player 2
		for (int i = 0; i < t1HandCountPlayer2; i++) {
			int randomCard = rand() % (treasure_map); // treasure map is the last card enum
			G1.hand[t1Player2][i] = randomCard;
		}
		
		// setup discard count for player 2
		G1.discardCount[t1Player2] = t1Player2DiscardCount;
		G1.deckCount[t1Player2] = t1Player2DeckCount;
		for (int i = 0; i < t1Player2DeckCount; i++) {
			if (i == 0) {
				G1.deck[t1Player2][0] = revealedCard1;
				if (revealedCard1 >= copper && revealedCard1 <= gold) { // revealed card is treasure
					hasTreasureCard = 1;
				}
				if (revealedCard1 >= adventurer) { // revealed card is action
					hasActionCard = 1;
				}
				if (revealedCard1 >= estate && revealedCard1 <= province){
					hasEstateCard = 1;
				}
			}
			if (i == 1){
				G1.deck[t1Player2][0] = revealedCard2;
				if (revealedCard2 >= copper && revealedCard2 <= gold) { // revealed card is treasure
					hasTreasureCard = 1;
				}
				if (revealedCard2 >= adventurer) { // revealed card is action
					hasActionCard = 1;
				}
				if (revealedCard2 >= estate && revealedCard2 <= province){
					hasEstateCard = 1;
				}
			}
		}
		
		
		memcpy(&G2, &G1, sizeof(struct gameState));
		tributeCardEffect(&G2, t1Player2, t1Player,tributeRevealedCards); // call the refactored function with newly created G2

		if ((G1.deckCount[t1Player2] == 0) && (G1.discardCount[t1Player2] == 0)) {
			test1Run = 1;
			printf("Opponent has no cards in discard or deck (assert no changes to their deck\n");
			customAssert(G1.deckCount[t1Player2], G2.deckCount[t1Player2]);
		} else if (G1.discardCount[t1Player2] == 0) {
			test4Run = 1;
			printf("Opponent has no cards in discard\n");
			customAssert(G1.deckCount[t1Player2], G2.deckCount[t1Player2]);
		}
		if (hasTreasureCard && hasActionCard){// Reveal a treasure card and action card (assert player should gain 2 gold then assert they gain 2 actions)
			test2Run = 1;
			printf("Reveal a treasure card and action card (assert player should gain 2 gold then assert they gain 2 actions\n");
			customAssert(G1.coins+2, G2.coins);
			customAssert(G1.numActions+2, G2.numActions);
		}
		if (hasEstateCard) {
			test3Run = 1;
			printf("Reveal a victory card (assert cards +2 for player)\n");
			customAssert(G1.handCount[t1Player], G2.handCount[t1Player] -2);
		}	
	}
	
	
	
	printf("Finished random testing for tribute card\n");
	printf("----------------------------------\n");
	return 0;
}