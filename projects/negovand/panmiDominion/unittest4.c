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
    int preActions;         //to hold numActions before function calls
    int preCoins;           //to hold coins before function calls

    // set card array
    int k[10] = { ambassador, council_room, tribute, gardens, mine
    , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G;
    int tributeRevealedCards[2] = {-1, -1};

    //--------------------------------------------------------------------------
    //TEST 4A: NEXT PLAYER HAS 2 OF THE SAME CARD IN DECK, ACTION 
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    int r = initializeGame(2, k, 15351, &G);

    printf("\n\nUNIT TEST 4 -- tributeCard() Test commencing!\n\n");
    printf("---------UNIT TEST 4A-------:\n");
    G.handCount[0] = 1;
    G.hand[0][0] = tribute;

    G.handCount[1] = 1;             //dummy hand for nextplayer
    G.hand[1][0] = copper;

    G.deckCount[1] = 2;             //nextplayer has 2 cards in deck
    G.deck[1][0] = ambassador;
    G.deck[1][1] = ambassador;                 
 
    preActions = G.numActions;
    preCoins = G.coins;
    test = tributeCard(&G, 1, 0, tributeRevealedCards);  //call function

    danAssert(test == 0, "4A: test didn't return an error");

    //current player should be down to 0 cards
    danAssert(G.handCount[0] == 0, "4A: G.handCount[0] == 0");
    //nextPlayer should have the same cards in hand as before
    danAssert(G.handCount[1] == 1, "4A: G.handCount[1] == 1");

    //currentplayer discard pile should have 1 tribute
    danAssert(G.discardCount[0] == 1, "4A: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == tribute, "4A: G.discard[0][0] == tribute");

    //nextplayer discard pile should have 2 ambassadors
    danAssert(G.discardCount[1] == 2, "4A: G.discardCount[1] == 2");
    danAssert(G.discard[1][0] == ambassador, "4A: G.discardCount[1][0] == ambassador");
    danAssert(G.discard[1][1] == ambassador, "4A: G.discardCount[1][1] == ambassador");

    //nextplayer deck should have 2 fewer cards
    danAssert(G.deckCount[1] == 0, "4A: G.deckCount[1] == 0");

    //numActions should only increase by 2
    danAssert(G.numActions == preActions+2, "4A: G.numActions == preActions+2");

    //coins should be unchanged
    danAssert(G.coins == preCoins, "4A: G.coins == preCoins");


    //--------------------------------------------------------------------------
    //TEST 4B: NEXT PLAYER HAS 0 CARDS IN DECK BUT 2 IN DISCARD PILE - BOTH TREASURE
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 4B-------:\n");
    G.handCount[0] = 1;
    G.hand[0][0] = tribute;

    G.handCount[1] = 1;             //dummy hand for nextplayer
    G.hand[1][0] = copper;

    G.deckCount[1] = 0;             //nextplayer has 2 cards in discard. 0 in deck
    G.discardCount[1] = 2;
    G.discard[1][0] = copper;        
    G.discard[1][1] = copper;            
 
    preActions = G.numActions;
    preCoins = G.coins;
    test = tributeCard(&G, 1, 0, tributeRevealedCards);  //call function

    danAssert(test == 0, "4B: test didn't return an error");

    //current player should be down to 0 cards
    danAssert(G.handCount[0] == 0, "4B: G.handCount[0] == 0");
    //nextPlayer should have the same cards in hand as before
    danAssert(G.handCount[1] == 1, "4B: G.handCount[1] == 1");

    //currentplayer discard pile should have 1 tribute
    danAssert(G.discardCount[0] == 1, "4B: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == tribute, "4B: G.discard[0][0] == tribute");

    //nextplayer discard pile should have 2 coppers
    danAssert(G.discardCount[1] == 2, "4B: G.discardCount[1] == 2");
    danAssert(G.discard[1][0] == copper, "4B: G.discardCount[1][0] == copper");
    danAssert(G.discard[1][1] == copper, "4B: G.discardCount[1][1] == copper");

    //nextplayer deck should still have 0 cards
    danAssert(G.deckCount[1] == 0, "4B: G.deckCount[1] == 0");

    //numActions should be unchanged
    danAssert(G.numActions == preActions, "4B: G.numActions == preActions");

    //coins should be +2
    danAssert(G.coins == preCoins+2, "4B: G.coins == preCoins+2");


    //--------------------------------------------------------------------------
    //TEST 4C: NEXT PLAYER HAS 2 DIFFERENT CARDS - VICTORY/TREASURE - 1 IN EACH
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 4C-------:\n");
    G.handCount[0] = 1;
    G.hand[0][0] = tribute;

    G.handCount[1] = 1;             //dummy hand for nextplayer
    G.hand[1][0] = copper;

    G.deckCount[1] = 1;             //nextplayer has 1 cards in discard. 1 in deck
    G.deck[1][0] = copper;  
    G.discardCount[1] = 1;
    G.discard[1][1] = duchy;            
 
    preActions = G.numActions;
    preCoins = G.coins;
    test = tributeCard(&G, 1, 0, tributeRevealedCards);  //call function

    danAssert(test == 0, "4C: test didn't return an error");

    //current player should now have 2 cards 
    danAssert(G.handCount[0] == 2, "4C: G.handCount[0] == 2");
    //nextPlayer should have the same cards in hand as before
    danAssert(G.handCount[1] == 1, "4C: G.handCount[1] == 1");

    //currentplayer discard pile should have 1 tribute
    danAssert(G.discardCount[0] == 1, "4C: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == tribute, "4C: G.discard[0][0] == tribute");

    //nextplayer discard pile should have the 2 revealed cards
    danAssert(G.discardCount[1] == 2, "4C: G.discardCount[1] == 2");

    //nextplayer deck should now have 0 cards
    danAssert(G.deckCount[1] == 0, "4C: G.deckCount[1] == 0");

    //numActions should be unchanged
    danAssert(G.numActions == preActions, "4C: G.numActions == preActions");

    //coins should be +2
    danAssert(G.coins == preCoins+2, "4C: G.coins == preCoins+2");


    //--------------------------------------------------------------------------
    //TEST 4D: NEXT PLAYER HAS 1 CARD - VICTORY
    //--------------------------------------------------------------------------
    // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 4D-------:\n");
    G.handCount[0] = 1;
    G.hand[0][0] = tribute;

    G.handCount[1] = 1;             //dummy hand for nextplayer
    G.hand[1][0] = copper;

    G.deckCount[1] = 1;             //nextplayer has 1 card in deck only
    G.deck[1][0] = duchy;  
    G.discardCount[1] = 0;          
 
    preActions = G.numActions;
    preCoins = G.coins;
    test = tributeCard(&G, 1, 0, tributeRevealedCards);  //call function

    danAssert(test == 0, "4D: test didn't return an error");

    //current player should now have 2 cards 
    danAssert(G.handCount[0] == 2, "4D: G.handCount[0] == 2");
    //nextPlayer should have the same cards in hand as before
    danAssert(G.handCount[1] == 1, "4D: G.handCount[1] == 1");

    //currentplayer discard pile should have 1 tribute
    danAssert(G.discardCount[0] == 1, "4D: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == tribute, "4D: G.discard[0][0] == tribute");

    //nextplayer discard pile should have the 2 revealed cards
    danAssert(G.discardCount[1] == 2, "4D: G.discardCount[1] == 2");

    //nextplayer deck should now have 0 cards
    danAssert(G.deckCount[1] == 0, "4D: G.deckCount[1] == 0");

    //numActions should be unchanged
    danAssert(G.numActions == preActions, "4D: G.numActions == preActions");

    //coins should be unchanged
    danAssert(G.coins == preCoins, "4D: G.coins == preCoins");


    //--------------------------------------------------------------------------
    //TEST 4E: BOUNDARY - CURRENT PLAYER IS LAST IN PLAYER ARRAY
    //--------------------------------------------------------------------------
     // set the state of variables
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(2, k, 15351, &G);

    printf("\n---------UNIT TEST 4E-------:\n");
    G.handCount[1] = 1;
    G.hand[1][0] = tribute;

    G.handCount[0] = 1;             //dummy hand for nextplayer
    G.hand[0][0] = copper;

    G.deckCount[0] = 1;             //nextplayer has 1 card in deck only
    G.deck[0][0] = duchy;  
    G.discardCount[0] = 0;          
 
    preActions = G.numActions;
    preCoins = G.coins;
    G.whoseTurn = 1;    //change currentPlayer around
    test = tributeCard(&G, 0, 1, tributeRevealedCards);  //call function

    danAssert(test == 0, "4E: test didn't return an error");

    //current player should now have 2 cards 
    danAssert(G.handCount[0] == 2, "4E: G.handCount[0] == 2");
    //nextPlayer should have the same cards in hand as before
    danAssert(G.handCount[1] == 1, "4E: G.handCount[1] == 1");

    //currentplayer discard pile should have 1 tribute
    danAssert(G.discardCount[0] == 1, "4E: G.discardCount[0] == 1");
    danAssert(G.discard[0][0] == tribute, "4E: G.discard[0][0] == tribute");

    //nextplayer discard pile should have the 2 revealed cards
    danAssert(G.discardCount[1] == 2, "4E: G.discardCount[1] == 2");

    //nextplayer deck should now have 0 cards
    danAssert(G.deckCount[1] == 0, "4E: G.deckCount[1] == 0");

    //numActions should be unchanged
    danAssert(G.numActions == preActions, "4E: G.numActions == preActions");

    //coins should be unchanged
    danAssert(G.coins == preCoins, "4E: G.coins == preCoins");



    printf("\nUNIT TEST 4 -- tributeCard() Test completed!\n\n");
    return 0;

}