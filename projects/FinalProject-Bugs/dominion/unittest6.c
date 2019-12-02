#include "dansFunctions.h"
#include "dominion.h"
#include <stdio.h>
#include <string.h>

void assert(int expression, char* testName) {
    if(expression) {
        printf("%s", testName);
        printf(" PASSED\n");
    }
    else {
        printf("%s", testName);
        printf(" FAILED\n");
    }
    return;
}


int main ()  {
    int test;
    //int preActions;
    //int preCoins;

    // set card array
    int k[10] = { ambassador, council_room, tribute, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;


   //--------------------------------------------------------------------------
    //Final project testing the Feast function in CardEffect
    //--------------------------------------------------------------------------
    // intialize a new game setting the state variables to a random seed
    // and make it two palyers :)
    memset(&G, 0, sizeof(struct gameState));
     int r = initializeGame(2, k, 15351, &G);




    printf("\n---------UNIT TEST Final - Feast function in card Effect-------:\n");



    //preActions = G.numActions;
    //preCoins = G.coins;
    //test = mineEffect(1, gold, &G, 0);  //call function
    test = cardEffect(feast, 1, 0, -1, &G, 0, -1);


    G.whoseTurn = 0;

    G.discardCount[0] = 4;
    G.handCount[0] = 4;
    G.coins = 4;



    assert(G.handCount > 4, "Test failed Player should have gained card");



    printf("\nUNIT TEST  -- Feast Test completed!\n\n");

    return 0;
}
