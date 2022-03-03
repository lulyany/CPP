//My Hand ADT implementation

#include "hand.h"

Hand::Hand()
{
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::discardAll()
{
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::addCard(Card c)
{
    int value = 0;
    if (c.spot <= 8)
        value = c.spot + 2;
    else if (c.spot <= 11)
        value = 10;
    else if (!(this->curValue.count < 21 && this->curValue.soft))
    {
        value = 11;
        this->curValue.soft = true;
    }
    else
        value = 1;

    this->curValue.count += value;

    if (this->curValue.soft && this->curValue.count > 21)
    {
        this->curValue.soft = false;
        this->curValue.count -= 10;
    }
}

HandValue Hand::handValue() const
{
    return this->curValue;
}