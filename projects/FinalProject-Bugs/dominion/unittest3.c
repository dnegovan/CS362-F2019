#include "dominion.h"
#include <stdio.h>
#include "dansFunctions.h"
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
    int r = initializeGame(2, k, 100, &G);

    printf("\n---------UNIT TEST Final remodel 1-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = remodel;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
           
 
    //preActions = G.numActions;
    //preCoins = G.coins;
    //test = mineEffect(1, gold, &G, 0);  //call function
    test = cardEffect(remodel, 1, gold, -1, &G, 0, -1);
    assert(test == -1, "test should return error because of illegal input. Result:");


//Test2
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(2, k, 100, &G);

    printf("\n---------UNIT TEST Final remodel 2-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = remodel;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
           
 
    //preActions = G.numActions;
    //preCoins = G.coins;
    //test = mineEffect(1, gold, &G, 0);  //call function
    test = cardEffect(remodel, 1, council_room, -1, &G, 0, -1);
    assert(test == -1, "test should return error because of illegal input. Result:");

    printf("\nUNIT TEST  -- remodel Test completed!\n\n");
    return 0;
}