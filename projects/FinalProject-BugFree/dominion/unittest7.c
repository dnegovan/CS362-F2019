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
    //Final project testing the Tribute card itterations for discarding the other players deck
    //--------------------------------------------------------------------------
    // intialize a new game setting the state variables to a random seed
    // and make it two palyers :)
      memset(&G, 0, sizeof(struct gameState));  //seteting a new  game state
      int r = initializeGame(2, k, 15351, &G);   // ititilizing the new gamestate




    printf("\n---------UNIT TEST BUG 7 TESTING TRIBUTE CARD FUNCTION ITTERATIONS -------:\n");


      int bonus = 0;

      test = cardEffect(tribute, 1, 0, -1, &G, 0, &bonus); //callig tributeCard function


      G.whoseTurn = 0; //setting the player playing the card
      G.coins = 0; //setting coins
      G.hand[1][0] = copper;
      G.hand[1][1] = copper;
      G.hand[1][2] = copper;
      G.discardCount[1] = 0;




    assert(G.discardCount[1] = 2 , "Test Failed too many Cards were discarded ");

          printf("\nUNIT TEST  -- Tribute Card Test itterations completed!\n\n");

    return 0;
}
