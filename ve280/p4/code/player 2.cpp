//My two player ADT implementations

#include "player.h"

//The simple player always places the minimum allowable wager,
//and decides to hit or stand based on the following rules
//and whether or not the player has a “hard count” or “soft count”
class Player_simple : public Player
{
public:
    Player_simple(){};
    //constructor

    int bet(unsigned int bankroll, unsigned int minimum);
    // EFFECTS: returns the player's bet, between minimum and bankroll
    // inclusive

    bool draw(Card dealer, const Hand &player);
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.

    void expose(Card c){};
    //EFFECTS: allows the player to "see" the newly-exposed card c.

    void shuffled(){};
    // EFFECTS: tells the player that the deck has been re-shuffled.
};

class Player_counting : public Player_simple
{
private:
    int icount;

public:
    Player_counting() { icount = 0; };
    // constructer: set count to 0

    int bet(unsigned int bankroll, unsigned int minimum);
    // EFFECTS: returns the player's bet, between minimum and bankroll
    // inclusive

    void expose(Card c);
    //EFFECTS: allows the player to "see" the newly-exposed card c.

    void shuffled() { icount = 0; };
    // EFFECTS: tells the player that the deck has been re-shuffled.
};

//methods
//simple player
int Player_simple::bet(unsigned int bankroll, unsigned int minimum)
{
    return minimum;
}

bool Player_simple::draw(Card dealer, const Hand &player)
{
    if (!player.handValue().soft)
    {
        if (player.handValue().count <= 11)
            return true;
        if (player.handValue().count == 12)
        {
            if (dealer.spot == FOUR || dealer.spot == FIVE || dealer.spot == SIX)
                return false;
            else
                return true;
        }
        if (player.handValue().count <= 16)
        {
            if ((int)dealer.spot <= 4)
                return false;
            else
                return true;
        }
        else
            return false;
    }
    else
    {
        if (player.handValue().count >= 19 || (player.handValue().count == 18 && (dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT)))
            return false;
        else
            return true;
    }
}

//methods
//counting player
int Player_counting::bet(unsigned int bankroll, unsigned int minimum)
{
    if (icount >= 2 && bankroll >= 2 * minimum)
        return (2 * minimum);
    return minimum;
}

void Player_counting::expose(Card c)
{
    if (c.spot >= 8)
        this->icount--;
    if (c.spot <= 4)
        this->icount++;
}

static Player_simple psimple;
static Player_counting pcounting;

Player *get_Simple()
{
    return &psimple;
}

Player *get_Counting()
{
    return &pcounting;
}
