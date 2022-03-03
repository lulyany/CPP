//My simulation driver

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

using namespace std;

void shuffle(Deck &deck, Player * player);
void print_card(const Card &card);
Card deal(Deck &deck, Hand &hand, Player *player, int test);
bool player_deal(Hand &hand_player, Deck &deck, int &bankroll, const int &wager, Player *player, const Card &dealer_faceup);
void dealer_deal(const Card &dealer_facedown, Player *player, Hand &hand_dealer, Deck &deck);
void get_result(const Hand &hand_dealer, const Hand &hand_player, int &bankroll, const int &wager);
void stimulate(int &bankroll, int &hands, Deck &deck, Player *player, Hand &hand_player, Hand &hand_dealer);

//main
int main(int argc, char *argv[])
{
    //read the input arguments
    //initialization bankroll and hands
    int ibankroll(atoi(argv[1]));
    int ihands(atoi(argv[2]));
    Deck deck;
    Hand hand_player;
    Hand hand_dealer;
    Player *player_boss;
    //judge player type

    if ((string)argv[3] == "simple")
        player_boss = get_Simple();
    else
        player_boss = get_Counting();

    //shuffling
    shuffle(deck, player_boss);

    //stimulate
    stimulate(ibankroll, ihands, deck, player_boss, hand_player, hand_dealer);
}

void shuffle(Deck &deck, Player * player)
{
    cout << "Shuffling the deck" << endl;
    for (int i = 0; i < 7; i++)
    {
        int icut = get_cut();
        deck.shuffle(icut);
        cout << "cut at " << icut << endl;
    }
    //tells the player that the deck has been reshuffled.
    player->shuffled();
}

// print cards
void print_card(const Card &card)
{
    cout << SpotNames[card.spot] << " of " << SuitNames[card.suit] << endl;
}

//deal
Card deal(Deck &deck, Hand &hand, Player *player, int flag)
{
    Card card = deck.deal();

    if (flag != 3)
        player->expose(card);
    hand.addCard(card);
    if (flag == 1)
    {
        cout << "Player dealt ";
        print_card(card);
    }
    else if (flag == 2)
    {
        cout << "Dealer dealt ";
        print_card(card);
    }
    return card;
}

//  the player's turn to draw card?return true if natural 21
bool player_deal(Hand &hand_player, Deck &deck, int &bankroll, const int &wager, Player *player, const Card &dealer_faceup)
{
    // got natural 21
    if (hand_player.handValue().count == 21 && hand_player.handValue().soft)
    {

        cout << "Player dealt natural 21\n";

        bankroll += (int)(1.5 * wager);
        return true;
    }
    while ((hand_player.handValue().count) <= 21 && player->draw(dealer_faceup, hand_player))
    {
        deal(deck, hand_player, player, 1);
    }

    cout << "Player's total is " << hand_player.handValue().count << endl;
    
    return false;
}

// dealer's turn to draw card?
void dealer_deal(const Card &dealer_facedown, Player *player, Hand &hand_dealer, Deck &deck)
{
    cout << "Dealer's hole card is ";
    print_card(dealer_facedown);

    player->expose(dealer_facedown);  

    while (hand_dealer.handValue().count < 17)
    {
        deal(deck, hand_dealer, player, 2);
    }
    cout << "Dealer's total is " << hand_dealer.handValue().count << endl;
}

// compare if either bust
void get_result(const Hand &hand_dealer, const Hand &hand_player, int &bankroll, const int &wager)
{
    if (hand_dealer.handValue().count > hand_player.handValue().count)
    {

        cout << "Dealer wins" << endl;
        bankroll -= wager;
    }
    else if (hand_dealer.handValue().count < hand_player.handValue().count)
    {

        cout << "Player wins" << endl;
        bankroll += wager;
    }
    else
        cout << "Push" << endl;
}

// the program driver
void stimulate(int &bankroll, int &hands, Deck &deck, Player *player, Hand &hand_player, Hand &hand_dealer)
{
    // start a hand
    int hand_it = 0;

    while (hand_it < hands)
    {

        //clean all cards
        hand_dealer.discardAll();
        hand_player.discardAll();

        // out of money
        if (bankroll < 5)
            break;
        hand_it++;

        cout << "Hand " << hand_it << " bankroll " << bankroll << endl;

        if (deck.cardsLeft() < 20)
        {
            shuffle(deck, player);
        }

        // player bets
        int wager = player->bet(bankroll, 5);
        cout << "Player bets " << wager << endl;

        // deal cards
        deal(deck, hand_player, player, 1);
        Card dealer_faceup = deal(deck, hand_dealer, player, 2);

        deal(deck, hand_player, player, 1);
        Card dealer_facedown = deal(deck, hand_dealer, player, 3);

        // player draws
        if (player_deal(hand_player, deck, bankroll, wager, player, dealer_faceup))
            continue; // get a natural 21
        // if player bust
        if (hand_player.handValue().count > 21)
        {

            cout << "Player busts" << endl;

            bankroll -= wager;
        }
        else
        {
            // player not bust and dealer draws
            dealer_deal(dealer_facedown, player, hand_dealer, deck);

            // dealer bust
            if (hand_dealer.handValue().count > 21)
            {

                cout << "Dealer busts" << endl;
                bankroll += wager;
            }
            else
                get_result(hand_dealer, hand_player, bankroll, wager);
        }
    }

    cout << "Player has " << bankroll
         << " after " << hand_it << " hands" << endl;
}