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

    // set card array
    int k[10] = { ambassador, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST 3A: REVEAL CARD, RETURN 0 COPIES TO SUPPLY
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    int r = initializeGame(3, k, 15351, &G);

    printf("\n\nUNIT TEST 3 -- ambassadorEffect() Test commencing!\n\n");
    printf("---------UNIT TEST 3A-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = mine;            //card to reveal in pos 1
    G.hand[0][2] = ambassador;      //ambassador in position 2

    G.handCount[1] = 2;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;                 

    G.handCount[2] = 4;
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;           
    G.hand[2][2] = copper;    
    G.hand[2][3] = copper;   

    int preSupply = G.supplyCount[mine];
    test = ambassadorEffect(1, 0, &G, 2);  //call function

    //player should be down to 2 cards
    danAssert(G.handCount[0] == 2, "3A: G.handCount[0] == 2");
    //other players should have 1 more card(mine) than before
    danAssert(G.handCount[1] == 3, "3A: G.handCount[1] == 3");
    danAssert(G.handCount[2] == 5, "3A: G.handCount[2] == 5");
    danAssert(G.hand[1][2] == mine, "3A: G.hand[1][2] == mine");
    danAssert(G.hand[2][4] == mine, "3A: G.hand[2][4] == mine");

    //discard pile should have 1 ambassador
    danAssert(G.discardCount[0] == 1, "3A: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == ambassador, "3A: G.discardCount[0][0] == ambassador");

    //supply of mines(revealed card) should be 2 fewer (other 2 players each got 1)
    danAssert(G.supplyCount[mine] == preSupply-2, "3A: G.supplyCount[mine] == preSupply-2");
    

    //--------------------------------------------------------------------------
    //TEST 3B: REVEAL CARD, RETURN 1 COPY TO SUPPLY
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(3, k, 15351, &G);

    printf("\n---------UNIT TEST 3B-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = mine;            //card to reveal in pos 1
    G.hand[0][2] = ambassador;      //ambassador in position 2

    G.handCount[1] = 2;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;                 

    G.handCount[2] = 4;
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;           
    G.hand[2][2] = copper;    
    G.hand[2][3] = copper;   

    preSupply = G.supplyCount[mine];
    test = ambassadorEffect(1, 1, &G, 2);  //call function

    //player should be down to 1 card
    danAssert(G.handCount[0] == 1, "3B: G.handCount[0] == 1");
    //other players should have 1 more card(mine) than before
    danAssert(G.handCount[1] == 3, "3B: G.handCount[1] == 3");
    danAssert(G.handCount[2] == 5, "3B: G.handCount[2] == 5");
    danAssert(G.hand[1][2] == mine, "3B: G.hand[1][2] == mine");
    danAssert(G.hand[2][4] == mine, "3B: G.hand[2][4] == mine");

    //discard pile should have 1 ambassador
    danAssert(G.discardCount[0] == 1, "3B: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == ambassador, "3B: G.discardCount[0][0] == ambassador");

    //supply of mines(revealed card) should be 1 fewer (2 players each got 1, but we put 1 in there)
    danAssert(G.supplyCount[mine] == preSupply-1, "3B: G.supplyCount[mine] == preSupply-1");


    //--------------------------------------------------------------------------
    //TEST 3C: REVEAL CARD, RETURN 2 COPIES TO SUPPLY
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(3, k, 15351, &G);

    printf("\n---------UNIT TEST 3C-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = mine;            //card to reveal in pos 1
    G.hand[0][2] = mine;      
    G.hand[0][3] = ambassador;      //ambassador in position 3

    G.handCount[1] = 2;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;                 

    G.handCount[2] = 4;
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;           
    G.hand[2][2] = copper;    
    G.hand[2][3] = copper;   

    preSupply = G.supplyCount[mine];
    test = ambassadorEffect(1, 2, &G, 3);  //call function

    //player should be down to 0 cards
    danAssert(G.handCount[0] == 0, "3C: G.handCount[0] == 0");
    //other players should have 1 more card(mine) than before
    danAssert(G.handCount[1] == 3, "3C: G.handCount[1] == 3");
    danAssert(G.handCount[2] == 5, "3C: G.handCount[2] == 5");
    danAssert(G.hand[1][2] == mine, "3C: G.hand[1][2] == mine");
    danAssert(G.hand[2][4] == mine, "3C: G.hand[2][4] == mine");

    //discard pile should have 1 ambassador
    danAssert(G.discardCount[0] == 1, "3C: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == ambassador, "3C: G.discardCount[0][0] == ambassador");

    //supply of mines(revealed card) should be = to before (2 players each got 1, but we put 2 in there)
    danAssert(G.supplyCount[mine] == preSupply, "3C: G.supplyCount[mine] == preSupply");

    //--------------------------------------------------------------------------
    //TEST 3D: BOUNDARY - CHOICE2 IS INVALID
    //--------------------------------------------------------------------------
     // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(3, k, 15351, &G);

    printf("\n---------UNIT TEST 3D-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = mine;
    G.hand[0][1] = mine;            //card to reveal in pos 1
    G.hand[0][2] = mine;      
    G.hand[0][3] = ambassador;      //ambassador in position 3

    G.handCount[1] = 2;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;                 

    G.handCount[2] = 4;
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;           
    G.hand[2][2] = copper;    
    G.hand[2][3] = copper;   

    preSupply = G.supplyCount[mine];
    test = ambassadorEffect(1, -1, &G, 3);  //call function

    //choosing -1 copies is invalid
    danAssert(test == -1, "3D: test == -1");




    printf("\nUNIT TEST 3 -- ambassadorEffect() Test completed!\n\n");
    return 0;

}