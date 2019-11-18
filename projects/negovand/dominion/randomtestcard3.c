#include "dominion.h"
#include "dansFunctions.h"
#include <stdio.h>



int main ()  {

    int test;               //holds results of function calls (-1, 0...)

    // declare the game state
    struct gameState G;

    //--------------------------------------------------------------------------
    //TEST 3: RANDOM TESTING tributeEffect()
    //--------------------------------------------------------------------------
    printf("\n\nUNIT TEST 3 -- tributeEffect() Test commencing!\n\n");

    //run this test 10000 times
    for (int i = 0; i < 10000; i++) {

        //SET UP THE GAME/ VARIABLES
        memset(&G, 0, sizeof(struct gameState));

        //custom initialize function that randomly sets up gamestate
        int r = randInitializeGame(&G);

        int tributePos = 0;
        //put tribute in random position of currentPlayer's hand
        if(G.handCount[G.whoseTurn] > 0) {
            tributePos = rand() % (G.handCount[G.whoseTurn] + 1);
            G.hand[G.whoseTurn][tributePos] = tribute;
        }

        //need to test with some more specific discard pile/deck options to get coverage
        for (int i=0; i < G.numPlayers; i++) {
            G.deckCount[i] = rand() % 4;
            //iterate through deck to add relevant possible cards
            for (int j = 0; j < G.deckCount[i]; j++) {
                int randVal = (rand() % 4) + 1;
            }

            G.discardCount[i] = rand() % 4;
            //iterate through discard pile to add relevant possible cards
            for (int j = 0; j < G.discardCount[i]; j++) {
                int randVal = (rand() % 4) + 1;
            }
        }

        //save some pre-function-call values to check
        int preCoins = G.coins;     
        int preActions = G.numActions;
        int preHandCount = G.handCount[G.whoseTurn];

        //store pre-function-call player hand counts
        int preDeckCount[G.numPlayers];
        for (int i = 0; i < G.numPlayers; i++) {
            preDeckCount[i] = G.deckCount[i];
        }

        //store nextPlayers top 2 cards (or 1 if they only have 1) in an array
        int nextPlayer = G.whoseTurn + 1;
        if (nextPlayer > (G.numPlayers - 1)) {
            nextPlayer = 0;
        }
        int nextTopTwo[2] = {-1, -1};
        int i = G.deckCount[nextPlayer]-1;  //iterate through deck
        int j = 0;  //count cards we've stored
        while (i >= 0 && j < 2) {
            nextTopTwo[j] = G.deck[nextPlayer][i];
            i--;
            j++;
        }

        //CALL FUNCTION
        test = tributeEffect(&G);  //call function

        
        //ASSERTS

        //test shouldn't have given error
        danAssert(test == 0, "Test3: test == 0, no error");

        //if nextTopTwo cards were the same, or they only had 1 card
        //first card should be the only one causing changes
        if(nextTopTwo[0] == nextTopTwo[1] || nextTopTwo[1] == -1) {
            //Treasure Card
            if (nextTopTwo[0] == copper || nextTopTwo[0] == silver 
                                        || nextTopTwo[0] == gold) { 
                danAssert(G.coins == preCoins+2, 
                          "Test3: 1 revealed card, coins=precoins + 2");

                //handCount is down 1 from playing tribute
                danAssert(G.handCount[G.whoseTurn] == preHandCount-1,
                          "Test3: 1 revealed card handCount == preHandCount-1");

                //actions unchanged
                danAssert(G.numActions == preActions,
                          "Test3: 1 revealed card, G.numActions = preActions");
            }
             //Victory Card 
            else if (nextTopTwo[0] == estate || nextTopTwo[0] == duchy 
                                             || nextTopTwo[0] == province 
                                             || nextTopTwo[0] == gardens 
                                             || nextTopTwo[0] == great_hall) {
                //currentPlayer played tribute but gained 2 cards, up 1
                danAssert(G.handCount[G.whoseTurn] == preHandCount+1,
                          "Test3: 1 revealed card, handcount = pre+1");

                //coins unchanged
                danAssert(G.coins == preCoins, 
                          "Test3: 1 revealed card, coins=precoins");

                //actions unchanged
                danAssert(G.numActions == preActions,
                          "Test3: 1 revealed card, G.numActions = preActions");
            
            }
            else { //Action Card
                danAssert(G.numActions == preActions + 2,
                          "Test3: 1 revealed card, G.numActions = preActions + 2");

                //handCount is down 1 from playing tribute
                danAssert(G.handCount[G.whoseTurn] == preHandCount-1,
                          "Test3: 1 revealed card handCount == preHandCount-1");

                //coins unchanged
                danAssert(G.coins == preCoins, 
                          "Test3: 1 revealed card, coins=precoins");
            }
        }

        //otherwise check that both cards had their effect
        else {
            for (int i = 0; i < 2; i++) {
                //Treasure Card
                if (nextTopTwo[i] == copper || nextTopTwo[i] == silver 
                                            || nextTopTwo[i] == gold) { 
                    danAssert(G.coins == preCoins+2, 
                            "Test3: 1 revealed card, coins=precoins + 2");
                }
                //Victory Card 
                else if (nextTopTwo[i] == estate || nextTopTwo[i] == duchy 
                                                || nextTopTwo[i] == province 
                                                || nextTopTwo[i] == gardens 
                                                || nextTopTwo[i] == great_hall) {
                    //currentPlayer played tribute but gained 2 cards, up 1
                    danAssert(G.handCount[G.whoseTurn] == preHandCount+1,
                            "Test3: 1 revealed card, handcount = pre+1");
                }
                else { //Action Card
                    danAssert(G.numActions == preActions + 2,
                            "Test3: 1 revealed card, G.numActions = preActions + 2");
                }
            }
        }

        //check that nextPlayers deck is down 2 if it had at least 2
        if (preDeckCount[nextPlayer] > 1) {
            danAssert(G.deckCount[nextPlayer] == preDeckCount[nextPlayer]-2, 
                        "Test3: nextPlayer deck == pre-2");
        }
        //otherwise that it lost 1 card if it only had one card
        else if (preDeckCount[nextPlayer] == 1) {
            danAssert(G.deckCount[nextPlayer] == 0, 
                        "Test3: nextPlayer deck == 0");
        }
        //otherwise they must have had 0, had to shuffle so it should have more than 1
        else {
            danAssert(G.deckCount[nextPlayer] > 1, 
                        "Test3: nextPlayer deck > 1");
        }
        
    }
    
    printf("\nUNIT TEST 3 -- tributeEffect() Test completed!\n\n");
    return 0;

}