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
    int test2;
    int test3;
    //int preActions;
    //int preCoins;

    // set card array
    int k[10] = { ambassador, council_room, tribute, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;


   //--------------------------------------------------------------------------
    //Final project testing the scoreFor function
    //--------------------------------------------------------------------------
    // intialize a new game setting the state variables to a random seed
    // and make it two palyers :)
    memset(&G, 0, sizeof(struct gameState));
     int r = initializeGame(2, k, 15351, &G);




    printf("\n---------UNIT TEST Final - ScoreFor function-------:\n");




    r = scoreFor(2, &G);


    G.handCount[0] = 1;
    G.handCount[1] = 1;
    G.hand[0][0] = duchy;
    G.hand[1][0] = duchy;

    G.discardCount[0] = 0;
    G.discardCount[1] = 0;
    G.deck[0][0] = duchy;
    G.deck[1][0] = estate;

    fullDeckCount(0, 0, &G);
    int i = 0;

      if(fullDeckCount) {
        i +1;

      }


      assert(i < 2 , "Test Failed  ");
      printf("\nUNIT TEST  -- Score for function is complete !\n\n");
    return 0;
}
