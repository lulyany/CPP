//My Deck ADT implementation

#include "deck.h"

Deck::Deck()
{
    int num = 0;
    for (int i = 0; i <= 3; i++)
    {
        for (int j = 0; j <= 12; j++)
        {
            deck[num].spot = static_cast<Spot>(j);
            deck[num].suit = static_cast<Suit>(i);
            num++;
        }
    }
    next = 0;
}

void Deck::reset()
{
    Deck deck_another;
    *this = deck_another;
}

void Deck::shuffle(int n)
{
    // separate into 2 segments
    Card left[n];
    Card right[DeckSize - n];

    for (int i = 0; i < DeckSize; i++)
    {
        (i < n) ? (left[i] = deck[i]) : (right[i - n] = deck[i]);
    }

    int deck_smaller = ((n > 26) ? (52 - n) : n);

    //refill
    for (int i = 0; i < deck_smaller; i++)
    {
        this->deck[2 * i] = right[i];
        this->deck[2 * i + 1] = left[i];
    }

    if (n < 26)
    {
        for (int i = deck_smaller; i < 52 - deck_smaller; i++)
        {
            this->deck[i + deck_smaller] = right[i];
        }
    }
    else
    {
        for (int i = deck_smaller; i < n; i++)
        {
            this->deck[i + deck_smaller] = left[i];
        }
    }
    this->next = 0;
}

Card Deck::deal()
{
    if (this->next == DeckSize)
        throw DeckEmpty();
    this->next++;
    return this->deck[this->next - 1];
}

int Deck::cardsLeft()
{
    return (DeckSize - (this->next));
}