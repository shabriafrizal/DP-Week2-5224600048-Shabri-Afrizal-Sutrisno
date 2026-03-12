#include "Deck.h"
#include <algorithm>
#include <random>

void Deck::createStarterDeck()
{
    cards.clear();

    for (int s = 0; s < 4; s++)
    {
        for (int r = 2; r <= 14; r++)
        {
            cards.emplace_back(
                (Suit)s,
                (Rank)r);
        }
    }
}

void Deck::shuffle()
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    std::shuffle(cards.begin(),
                 cards.end(), g);
}

Card Deck::draw()
{
    Card c = cards.back();
    cards.pop_back();
    return c;
}

bool Deck::empty() const
{
    return cards.empty();
}

int Deck::size() const
{
    return cards.size();
}