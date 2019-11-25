#include "dominion.h"
#include <string.h>
#include <stdio.h>

void danAssert(int expression, char* testName) {
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

    int test;               //holds results of function calls (-1, 0...)
    int preActions;         //to hold numActions before function calls
    int preCoins;           //to hold coins before function calls

    // set card array
    int k[10] = { ambassador, council_room, tribute, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST 5A: TRASH COPPER, GAIN SILVER
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    int r = initializeGame(2, k, 15351, &G);

    printf("\n\nUNIT TEST 5 -- mineCard() Test commencing!\n\n");
    printf("---------UNIT TEST 5A-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;
           
 
    preActions = G.numActions;
    preCoins = G.coins;
    test = mineCard(&G, 0, 1, silver, 0);  //call function

    danAssert(test == 0, "5A: test didn't return an error");

    //current player hand should not have the mine anymore
    danAssert(G.handCount[0] == 2, "5A: G.handCount[0] == 2");

    //current player should have silver now
    danAssert(G.hand[0][2] == silver, "5A: G.hand[0][2] == silver");

    //currentplayer discard pile should have 1 copper
    danAssert(G.discardCount[0] == 1, "5A: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == copper, "5A: G.discard[0][0] == copper");

    //coins should be unchanged
    danAssert(G.coins == preCoins, "5A: G.coins == preCoins");


    //--------------------------------------------------------------------------
    //TEST 5B: TRASH SILVER, GAIN GOLD
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 5B-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
           
 
    preActions = G.numActions;
    preCoins = G.coins;
    test = mineCard(&G, 0, 1, gold, 0);  //call function

    danAssert(test == 0, "5B: test didn't return an error");

    //current player hand should not have the mine anymore
    danAssert(G.handCount[0] == 2, "5B: G.handCount[0] == 2");

    //current player should have gold now
    danAssert(G.hand[0][2] == gold, "5B: G.hand[0][2] == gold");

    //currentplayer discard pile should have 1 silver
    danAssert(G.discardCount[0] == 1, "5B: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == silver, "5B: G.discard[0][0] == silver");

    //coins should be unchanged
    danAssert(G.coins == preCoins, "5B: G.coins == preCoins");


    //--------------------------------------------------------------------------
    //TEST 5C: BOUNDARY TEST - INVALID CHOICE, GAIN NON-TREASURE CARD
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 5C-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
           
 
    preActions = G.numActions;
    preCoins = G.coins;
    test = mineCard(&G, 0, 1, tribute, 0);  //call function

    //should get an error
    danAssert(test == -1, "5C: test correctly returned an error");

    //--------------------------------------------------------------------------
    //TEST 5D: BOUNDARY TEST - INVALID CHOICE, GAIN GARBAGE VALUE
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 5D-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
           
 
    preActions = G.numActions;
    preCoins = G.coins;
    test = mineCard(&G, 0, 1, 75, 0);  //call function

    //should get an error
    danAssert(test == -1, "5D: test correctly returned an error");



    printf("\nUNIT TEST 5 -- mineCard() Test completed!\n\n");
    return 0;
}