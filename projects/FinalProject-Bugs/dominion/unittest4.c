#include "dominion.h"
#include <stdio.h>
#include 'dansFunction.h'





int main ()  {


    int test;              
    int preActions;         
    int preCoins;     
    printf ("in bug4test\n");

    // set card array
    int k[10] = { ambassador, council_room, tribute, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;


   //--------------------------------------------------------------------------
    //TEST final: Set 3 piles of card to empty
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    int r = initializeGame(2, k, 100, &G);

    printf("\n---------UNIT TEST Final-------:\n");
    G.handCount[0] = 3;
    G.hand[0][0] = remodel;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
    G.supplyCount[26] = 0;
    G.supplyCount[22] = 0;
    G.supplyCount[20] = 0;
    
           
 
    preActions = G.numActions;
    preCoins = G.coins;
    //test = mineEffect(1, gold, &G, 0);  //call function
    test = isGameOver(&G);
    danAssert(test == 1, "test should return true because of 3 piles in supply count empty. Result:");




    printf("\nUNIT TEST  -- isGameOver() Test completed!\n\n");
   
    return 0;
}