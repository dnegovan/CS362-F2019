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


int main ()  {
    int test;               //holds results of function calls (-1, 0...)

    // set card array
    int k[10] = { minion, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST 2A: ADD 2 COINS
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 23, sizeof(struct gameState));
    int r = initializeGame(3, k, 15351, &G);

    printf("\n\nUNIT TEST 2 -- minionCard() Test commencing!\n\n");
    printf("---------UNIT TEST 2A-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = minion;      //minion in position 2

    int preCoins = G.coins;     //save coin amt before function call
    int preActions = G.numActions;     //save numActions amt before function call
    test = minionCard(&G, 2, G.whoseTurn, 1, 0);  //call function
    
    //coin amount should increase by 2
    danAssert(G.coins == preCoins+2, "2A: G.coins == preCoins+2");

    //num actions should increase by 1
    danAssert(G.numActions == preActions+1, "2A: G.numActions == preActions+1");

    //player should now have 2 cards
    danAssert(G.handCount[0] == 2, "2A: G.handCount[0] == 2");

    //discard pile should have 1 minion
    danAssert(G.discardCount[0] == 1, "2A: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == minion, "2A: G.discardCount[0][0] == minion");


    //--------------------------------------------------------------------------
    //TEST 2B: DISCARD HAND - 2 OTHER PLAYERS EACH WITH >=5 CARDS
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(3, k, 15351, &G);

    printf("\n---------UNIT TEST 2B-------:\n");
    G.handCount[0] = 5;
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = minion;      //minion in position 2
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;

    G.handCount[1] = 5;         
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.hand[1][2] = copper;      
    G.hand[1][3] = copper;
    G.hand[1][4] = copper;

    G.handCount[2] = 7;         
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;
    G.hand[2][2] = copper;      
    G.hand[2][3] = copper;
    G.hand[2][4] = copper;
    G.hand[2][5] = copper;
    G.hand[2][6] = copper;
    preCoins = G.coins;     //save coin amt before function call
    preActions = G.numActions;     //save numActions amt before function call
    test = minionCard(&G, 2, G.whoseTurn, 0, 1);  //call function
    
    //coin amount should be unchanged
    danAssert(G.coins == preCoins, "2B: G.coins == preCoins");
    //num actions should increase by 1
    danAssert(G.numActions == preActions+1, "2B: G.numActions == preActions+1");

    //players should all now have 4 cards
    danAssert(G.handCount[0] == 4, "2B: G.handCount[0] == 4");
    danAssert(G.handCount[1] == 4, "2B: G.handCount[1] == 4");
    danAssert(G.handCount[2] == 4, "2B: G.handCount[2] == 4");

    //discard piles should have 5, 5, 7
    danAssert(G.discardCount[0] == 5, "2B: G.discardCount[0] == 5");
    danAssert(G.discardCount[1] == 5, "2B: G.discardCount[1] == 5");
    danAssert(G.discardCount[2] == 7, "2B: G.discardCount[2] == 7");

    //--------------------------------------------------------------------------
    //TEST 2C: DISCARD HAND - 1 OTHER PLAYER WITH >=5 CARDS
    //--------------------------------------------------------------------------
     // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(3, k, 15351, &G);

    printf("\n---------UNIT TEST 2C-------:\n");
    G.handCount[0] = 5;
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = minion;      //minion in position 2
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;

    G.handCount[1] = 5;         
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.hand[1][2] = copper;      
    G.hand[1][3] = copper;
    G.hand[1][4] = copper;

    G.handCount[2] = 2;         
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;

    preCoins = G.coins;     //save coin amt before function call
    preActions = G.numActions;     //save numActions amt before function call
    test = minionCard(&G, 2, G.whoseTurn, 0, 1);  //call function
    
    //coin amount should be unchanged
    danAssert(G.coins == preCoins, "2C: G.coins == preCoins");
    //num actions should increase by 1
    danAssert(G.numActions == preActions+1, "2C: G.numActions == preActions+1");

    //current player should now have 4 cards
    danAssert(G.handCount[0] == 4, "2C: G.handCount[0] == 4");

    //next player should have 4 cards
    danAssert(G.handCount[1] == 4, "2C: G.handCount[1] == 4");

    //Last player should still have 2 cards
    danAssert(G.handCount[2] == 2, "2C: G.handCount[2] == 2");

    //discard piles should have 5, 5, 0
    danAssert(G.discardCount[0] == 5, "2C: G.discardCount[0] == 5");
    danAssert(G.discardCount[1] == 5, "2C: G.discardCount[1] == 5");
    danAssert(G.discardCount[2] == 0, "2C: G.discardCount[2] == 0");


    //--------------------------------------------------------------------------
    //TEST 2D: DISCARD HAND, 0 OTHER PLAYERS WITH 5 CARDS
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(3, k, 15351, &G);

    printf("\n---------UNIT TEST 2D-------:\n");
    G.handCount[0] = 5;
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;      
    G.hand[0][3] = copper;
    G.hand[0][4] = minion;      //minion in position 4

    G.handCount[1] = 3;         
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.hand[1][2] = copper;      

    G.handCount[2] = 2;         
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;

    preCoins = G.coins;     //save coin amt before function call
    preActions = G.numActions;     //save numActions amt before function call
    test = minionCard(&G, 4, G.whoseTurn, 0, 1);  //call function
    
    //coin amount should be unchanged
    danAssert(G.coins == preCoins, "2D: G.coins == preCoins");
    //num actions should increase by 1
    danAssert(G.numActions == preActions+1, "2D: G.numActions == preActions+1");

    //current player should now have 4 cards
    danAssert(G.handCount[0] == 4, "2D: G.handCount[0] == 4");

    //next players should have the same cards as before
    danAssert(G.handCount[1] == 3, "2D: G.handCount[1] == 3");
    danAssert(G.handCount[2] == 2, "2D: G.handCount[2] == 2");

    //discard piles should have 5, 0, 0
    danAssert(G.discardCount[0] == 5, "2D: G.discardCount[0] == 5");
    danAssert(G.discardCount[1] == 0, "2D: G.discardCount[1] == 0");
    danAssert(G.discardCount[2] == 0, "2D: G.discardCount[2] == 0");

    //--------------------------------------------------------------------------
    //TEST 2E: BOUNDARY -- MINION IS ONLY CARD
    //--------------------------------------------------------------------------
     // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(3, k, 15351, &G);

    printf("\n---------UNIT TEST 2E-------:\n");
    G.handCount[0] = 1;
    G.hand[0][1] = minion;      //minion in position 4

    G.handCount[1] = 5;         
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.hand[1][2] = copper;      
    G.hand[1][3] = copper;    
    G.hand[1][4] = copper;    

    G.handCount[2] = 2;         
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;

    preCoins = G.coins;     //save coin amt before function call
    preActions = G.numActions;     //save numActions amt before function call
    test = minionCard(&G, 4, G.whoseTurn, 0, 1);  //call function
    
    //coin amount should be unchanged
    danAssert(G.coins == preCoins, "2E: G.coins == preCoins");
    //num actions should increase by 1
    danAssert(G.numActions == preActions+1, "2E: G.numActions == preActions+1");

    //current player should now have 4 cards
    danAssert(G.handCount[0] == 4, "2E: G.handCount[0] == 4");
    //next player should have 4 cards
    danAssert(G.handCount[1] == 4, "2E: G.handCount[1] == 4");
    //last player should still have 2
    danAssert(G.handCount[2] == 2, "2E: G.handCount[2] == 2");

    //discard piles should have 1, 5, 0
    danAssert(G.discardCount[0] == 1, "2E: G.discardCount[0] == 1");
    danAssert(G.discardCount[1] == 5, "2E: G.discardCount[1] == 5");
    danAssert(G.discardCount[2] == 0, "2E: G.discardCount[2] == 0");



    printf("\nUNIT TEST 2 -- minionCard() Test completed!\n\n");
    return 0;


}