#include "dominion.h"
#include <stdio.h>
#include "dansFunctions.h"





int main ()  {

    int test;               //holds results of function calls (-1, 0...)

    // set card array
    int k[10] = { ambassador, council_room, tribute, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    int r = initializeGame(2, k, 15351, &G);

    printf("\n\nUNIT TEST BUG 1 -- Test commencing!\n\n");
    G.handCount[0] = 2;
    G.hand[0][0] = mine;
    G.hand[0][1] = copper;

    G.discardCount[0] = 0;  //empty discard pile for currentPlayer
           
    test = cardEffect(mine, 1, silver, -1, &G, 0, -1);  //call function

    //currentplayer discard pile should still be empty
    danAssert(G.discardCount[0] == 1, "BUG1: G.discardCount[0] == 0");

    printf("\nUNIT TEST BUG 1 -- Test completed!\n\n");
    return 0;
}