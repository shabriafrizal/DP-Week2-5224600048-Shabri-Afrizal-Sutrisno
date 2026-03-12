#pragma once
#include <vector>
#include <string>
#include "card/Card.h"

//--------------------------------
// Poker Hand Types
//--------------------------------
enum class HandRank
{
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    FiveOfAKind,
    FlushHouse,
    FlushFive
};

//--------------------------------
// Scoring System
//--------------------------------
class ScoringSystem
{
public:
    static HandRank evaluate(
        const std::vector<Card> &cards);

    static std::string
    rankToString(HandRank rank);

    static int calculateScore(HandRank rank, const std::vector<Card> &cards);
};