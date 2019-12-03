#include "dominion.h"
#include <stdio.h>
#include "dansFunctions.h"



int main ()  {

    int test;               //holds results of function calls (-1, 0...)

    // set card array
    int k[10] = { ambassador, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    int r = initializeGame(2, k, 15351, &G);  //2 player game

    printf("\n\nUNIT TEST BUG 10 -- Test commencing!\n\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = mine;            //card to reveal in pos 1
    G.hand[0][2] = mine;      
    G.hand[0][3] = ambassador;      //ambassador in position 3

    G.whoseTurn = 0;

    G.handCount[1] = 0;  //other player has no cards               

    test = cardEffect(ambassador, 1, 2, -1, &G, 3, -1);  //call function

    //current player 0 should be down to 1 cards
    danAssert(G.handCount[0] == 1, "BUG 10: G.handCount[0] == 1");
    //other players should have 1 more card(mine) than before
    danAssert(G.handCount[1] == 1, "BUG 10: G.handCount[1] == 1");

    printf("\nUNIT TEST BUG 10 -- Test completed!\n\n\n");
    return 0;
}