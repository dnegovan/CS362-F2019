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

    printf("\n---------UNIT TEST Bug 9 Commencing! -------:\n");

    G.whoseTurn = 0; //setting the player playing the card
    G.handCount[0] = 1;
    G.hand[0][0] = tribute;

    G.discardCount[1] = 0;
    G.deckCount[1] = 10;   //player to the left has all barons in deck, to make sure!!
    G.deck[1][9] = baron;
    G.deck[1][8] = baron;
    G.deck[1][7] = baron;
    G.deck[1][6] = baron;
    G.deck[1][5] = baron;
    G.deck[1][4] = baron;
    G.deck[1][3] = baron;
    G.deck[1][2] = baron;
    G.deck[1][1] = baron;
    G.deck[1][0] = baron;

    G.numActions = 0;

    test = cardEffect(tribute, 1, 0, -1, &G, 0, -1); //calling tributeCard function

    //should only get +2 actions, not 4
    assert(G.numActions == 2, "BUG9: numActions == 2");

    printf("\nUNIT TEST  -- BUG 9 completed!\n\n");

    return 0;
}
