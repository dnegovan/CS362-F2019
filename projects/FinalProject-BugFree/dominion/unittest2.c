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
    //TEST final: TRASH Copper, GAIN GOLD
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    int r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST Final - mine 1-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
           
 
    //preActions = G.numActions;
    //preCoins = G.coins;
    //test = mineEffect(1, gold, &G, 0);  //call function
    test = cardEffect(mine, 1, gold, -1, &G, 0, -1);
    assert(test == -1, "test should return an error for the invalid choices. Result: ");


    return 0;
}