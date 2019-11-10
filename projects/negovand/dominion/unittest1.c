#include "dominion.h"
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


//tests baronEffect function
int main ()  {

    int test;               //holds results of function calls (-1, 0...)

    // set card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST 1A:  DISCARD YES, ESTATE IN HAND
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 23, sizeof(struct gameState));
    int r = initializeGame(2, k, 15351, &G);

    printf("\n\nUNIT TEST 1 -- baronEffect() Test commencing!\n\n");
    printf("---------UNIT TEST 1A-------:\n");
    G.handCount[0] = 5;
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = estate;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    int preCoins = G.coins;     //save coin amt before function call
    test = baronEffect(1, &G);  //call function
    
    //discard pile should have one estate
    danAssert(G.discardCount[0] == 1, "1A: discardCount==1");
    danAssert(G.discard[0][0] == estate, "1A: discard[0][0] == estate");

    //hand should have 1 fewer cards, all coppers
    danAssert(G.handCount[0] == 4, "1A: handCount==4");
    for (int i = 0; i < 4; i++) {
        danAssert(G.hand[0][i] == copper, "1A: hand[0][x]==copper");
    }

    //buying power should be 4 coins more than before call
    danAssert(G.coins == preCoins+4, "1A: coins == pre+4");


    //--------------------------------------------------------------------------
    //TEST 1B: DISCARD YES, NO ESTATE IN HAND
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 1B-------:\n");
    G.handCount[0] = 5;
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;      //no estate in hand this time
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    preCoins = G.coins;     //save coin amt before function call
    int preEstateCount = G.supplyCount[estate];  //pre-function estate supply
    test = baronEffect(1, &G);  //call function
    
    //discard pile should be empty
    danAssert(G.discardCount[0] == 0, "1B: discardCount==0");

    //hand should have 1 more card, an estate (forced to take one)
    danAssert(G.handCount[0] == 6, "1B: handCount==6");
    danAssert(G.hand[0][5] == estate, "1B: hand[0][5]==estate");

    //buying power should be the same as before call
    danAssert(G.coins == preCoins, "1B: coins == pre");

    //estate count should be one fewer
    danAssert(G.supplyCount[estate] == preEstateCount-1, 
                                       "1B: G.supplyCount[estate] == preEstateCount-1");

    //--------------------------------------------------------------------------
    //TEST 1C: DISCARD NO
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 1C-------:\n");
    G.handCount[0] = 5;
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;      //no estate in hand this time
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    preCoins = G.coins;     //save coin amt before function call
    preEstateCount = G.supplyCount[estate];  //pre-function estate supply
    test = baronEffect(0, &G);  //call function
    
    //discard pile should be empty
    danAssert(G.discardCount[0] == 0, "1C: discardCount==0");

    //hand should have 1 more card, an estate (forced to take one)
    danAssert(G.handCount[0] == 6, "1C: handCount==6");
    danAssert(G.hand[0][5] == estate, "1C: hand[0][5]==estate");

    //buying power should be the same as before call
    danAssert(G.coins == preCoins, "1C: coins == pre");

    //estate count should be one fewer
    danAssert(G.supplyCount[estate] == preEstateCount-1, 
                                       "1C: G.supplyCount[estate] == preEstateCount-1");


    //--------------------------------------------------------------------------
    //TEST 1D: BOUNDARY CONDITION - EMPTY HAND
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 1D-------:\n");
    G.handCount[0] = 0;     //hand is empty

    preCoins = G.coins;     //save coin amt before function call
    preEstateCount = G.supplyCount[estate];  //pre-function estate supply
    test = baronEffect(0, &G);  //call function
    
    //discard pile should be empty
    danAssert(G.discardCount[0] == 0, "1D: discardCount==0");

    //hand should have 1 more card, an estate (forced to take one)
    danAssert(G.handCount[0] == 1, "1D: handCount==1");
    danAssert(G.hand[0][5] == estate, "1D: hand[0][0]==estate");

    //buying power should be the same as before call
    danAssert(G.coins == preCoins, "1D: coins == pre");

    //estate count should be one fewer
    danAssert(G.supplyCount[estate] == preEstateCount-1, 
                                       "1D: G.supplyCount[estate] == preEstateCount-1");

    //--------------------------------------------------------------------------
    //TEST 1E: BOUNDARY CONDITION - NO ESTATES LEFT
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 1E-------:\n");
    G.handCount[0] = 5;
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;      //no estate in hand this time
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    preCoins = G.coins;     //save coin amt before function call
    G.supplyCount[estate] = 0;  //NO ESTATES LEFT
    test = baronEffect(0, &G);  //call function
    
    //discard pile should be empty
    danAssert(G.discardCount[0] == 0, "1E: discardCount==0");

    //hand should still have 5 cards
    danAssert(G.handCount[0] == 5, "1E: handCount==5");

    //buying power should be the same as before call
    danAssert(G.coins == preCoins, "1E: coins == pre");

    //estate count should still be 0
    danAssert(G.supplyCount[estate] == 0, "1E: G.supplyCount[estate] == 0");



    printf("\nUNIT TEST 1 -- baronEffect() Test completed!\n\n");


    return 0;

}