#include "dominion.h"
#include "dansFunctions.h"
#include <stdio.h>


//tests baronCard function
int main ()  {

    int test;               //holds results of function calls (-1, 0...)

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST 1: RANDOM TESTING baronCard()
    //--------------------------------------------------------------------------
    printf("\n\nUNIT TEST 1 -- baronCard() Test commencing!\n\n");

    //run this test 2500 times
    for (int i = 0; i < 2500; i++) {

        //SET UP THE GAME/ VARIABLES
        memset(&G, 0, sizeof(struct gameState));

        //custom initialize function that randomly sets up gamestate
        int r = randInitializeGame(&G);

    
        //put baron in random position of currentPlayer's hand
        int baronPos = 0;
        if(G.handCount[G.whoseTurn] > 0) {
            baronPos = rand() % (G.handCount[G.whoseTurn] + 1);
            G.hand[G.whoseTurn][baronPos] = baron;
        }


        //randomly add an estate to currentPlayer's hand ~50% of the time
        int estatePos = 0;
        if (G.handCount[G.whoseTurn] > 0  && (rand() % 2) == 0) {
            estatePos = rand() % (G.handCount[G.whoseTurn] + 1);
            if (estatePos != baronPos) {
                G.hand[G.whoseTurn][estatePos] = estate;
            }
        }

        //now check if we have an estate
        int haveEstate = 0;
        for (int i=0; i < G.handCount[G.whoseTurn]; i++) {
            if(G.hand[G.whoseTurn][i] == estate) {
                haveEstate = 1;
            }
        }

        //save some pre-function-call values to check
        int preCoins = G.coins;     
        int preHandCount = G.handCount[G.whoseTurn];
        int preEstateCount = G.supplyCount[estate];

        //generate random choice1 value 0 or 1
        int choice1 = rand() % 2;



        //CALL FUNCTION
        test = baronCard(&G, choice1, G.whoseTurn);  //call function



        //ASSERTS
        //test shouldn't have given error
        danAssert(test == 0, "Test1: test == 0, no error");


        if (choice1 == 1 && haveEstate == 1) {
            //discard pile should have one estate
            danAssert(G.discardCount[0] == 1, "Test1: discardCount==1");
            danAssert(G.discard[0][0] == estate, "Test1: discard[0][0] == estate");

            //it should be gone from hand, along with baron
            danAssert(G.handCount[G.whoseTurn] == preHandCount-2, "Test1: handCount==preHandCount-1");

            //if choice 1=1 and we had an estate card, we should have 4 extra coins
            danAssert(G.coins == preCoins+4, "Test1: coins == preCoins+4");
        }
        else {  
            //discard unchanged
            danAssert(G.discardCount[0] == 0, "Test1: discardCount==0");

            //gained an estate but played baron, so handcount unchanged
            danAssert(G.handCount[G.whoseTurn] == preHandCount, "Test1: handCount==preHandCount");

            //buying power unchanged
            danAssert(G.coins == preCoins, "Test1: coins == preCoins");
        }
    
    }
    
    printf("\nUNIT TEST 1 -- baronCard() Test completed!\n\n");


    return 0;

}