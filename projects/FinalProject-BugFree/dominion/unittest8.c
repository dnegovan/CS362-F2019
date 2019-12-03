#include "dominion.h"
#include <stdio.h>
#include "dansFunctions.h"





int main ()  {

    int test;               //holds results of function calls (-1, 0...)

    // set card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 23, sizeof(struct gameState));
    int r = initializeGame(2, k, 15351, &G);

    printf("\n\nUNIT TEST BUG 8 -- Test commencing!\n\n");
    G.handCount[0] = 2;
    G.hand[0][0] = baron;
    G.hand[0][1] = estate;

    G.whoseTurn = 0;

    test = updateCoins(0, &G, 0);

    int preCoins = G.coins;     //save coin amt before function call

    test = playCard(0, 1, -1, -1, &G);  //call function

    //buying power should be 4 coins more than before call to playCard()
    danAssert(G.coins == preCoins+4, "BUG 8: coins == pre+4");

    printf("\nUNIT TEST BUG 8 -- Test completed!\n\n");
    return 0;
}