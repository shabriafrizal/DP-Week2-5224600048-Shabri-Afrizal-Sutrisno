#pragma once
#include <vector>
#include "Card.h"

class Deck
{
private:
    std::vector<Card> cards;

public:
    void createStarterDeck();
    void shuffle();
    Card draw();

    bool empty() const;
    int size() const;
};