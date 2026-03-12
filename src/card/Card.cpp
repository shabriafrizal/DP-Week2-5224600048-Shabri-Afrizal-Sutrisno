#include "Card.h"

Card::Card(Suit s, Rank r)
    : suit(s), rank(r) {}

Suit Card::getSuit() const
{
    return suit;
}

Rank Card::getRank() const
{
    return rank;
}

std::string Card::toString() const
{

    static const std::string suits[] =
        {"H", "D", "C", "S"};

    static const std::string ranks[] =
        {"", "",
         "2", "3", "4", "5", "6", "7",
         "8", "9", "10",
         "J", "Q", "K", "A"};

    return ranks[(int)rank] +
           suits[(int)suit];
}

bool Card::operator<(const Card &other) const
{
    // Higher rank first
    if (rank != other.rank)
        return (int)rank > (int)other.rank;

    // Suit order
    // Spades > Hearts > Diamonds > Clubs
    return (int)suit > (int)other.suit;
}