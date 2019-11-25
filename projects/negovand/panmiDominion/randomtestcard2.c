#include "dominion.h"
#include "dansFunctions.h"
#include <stdio.h>

int main ()  {

    int test;               //holds results of function calls (-1, 0...)

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST 2: RANDOM TESTING minionCard()
    //--------------------------------------------------------------------------
    printf("\n\nUNIT TEST 2 -- minionCard() Test commencing!\n\n");

    //run this test 2500 times
    for (int i = 0; i < 2500; i++) {

        //SET UP THE GAME/ VARIABLES
        memset(&G, 0, sizeof(struct gameState));

        //custom initialize function that randomly sets up gamestate
        int r = randInitializeGame(&G);


        int minionPos = 0;
        //put minion in random position of currentPlayer's hand
        if(G.handCount[G.whoseTurn] > 0) {
            minionPos = rand() % (G.handCount[G.whoseTurn] + 1);
            G.hand[G.whoseTurn][minionPos] = minion;
        }
        
       

        //save some pre-function-call values to check
        int preCoins = G.coins;     
        int preActions = G.numActions;

        //store pre-function-call player hand counts
        int preHandCount[G.numPlayers];
        for (int i = 0; i < G.numPlayers; i++) {
            preHandCount[i] = G.handCount[i];
        }

        //generate random choice1 value: both 0 or 1
        int choice1 = rand() % 2;

        //choice 2 is redundant, just putting 1
        //CALL FUNCTION
        test = minionCard(&G, minionPos, G.whoseTurn, choice1, 1);  //call function

        
        //ASSERTS

        //test shouldn't have given error
        danAssert(test == 0, "Test2: test == 0, no error");

        //numActions should increase by 1 no matter what
        danAssert(G.numActions == preActions+1, "Test2: G.numActions == preActions+1");

        //if choice1, we just get coins
        if (choice1 == 1) {
            //coins should be +2
            danAssert(G.coins == preCoins+2, "Test2: G.coins == preCoins+2");

            //minion alone should not be in hand anymore
            danAssert(G.handCount[G.whoseTurn] == preHandCount[G.whoseTurn] - 1, 
                        "Test2: choice1, current handCount = preHandCount -1");
        }
        else {
            //coin amount should be unchanged
            danAssert(G.coins == preCoins, "Test2: G.coins == preCoins");

            //currentPlayer and any player that had 5 cards should now have 4 cards
            for (int i = 0; i < G.numPlayers; i++) {
                if(i == G.whoseTurn) {
                    danAssert(G.handCount[i] == 4, "Test2: Currentplayer handCount == 4");

                    //discard pile should have all of the old cards
                    danAssert(G.discardCount[i] == preHandCount[i], 
                                "Test2: currentPlayer new discardCount == preHandCount");
                }
                else if (preHandCount[i] > 4) {
                    danAssert(G.handCount[i] == 4, "Test2: Other players w 5+ cards handCount == 4");
                    //discard pile should have all of the old cards
                    danAssert(G.discardCount[i] == preHandCount[i], 
                                "Test2: other players w 5+ cards discardCount == preHandCount");
                }
                else {
                    //player didn't have 5 cards, hand should be unchanged
                    danAssert(G.handCount[i] == preHandCount[i], "Test2:G.handCount[i] == preHandCount[i]");
                }
            }
        }
    
    }
    
    printf("\nUNIT TEST 2 -- minionCard() Test completed!\n\n");

    return 0;


}