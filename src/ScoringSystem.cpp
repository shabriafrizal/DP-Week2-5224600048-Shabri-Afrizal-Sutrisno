#include "ScoringSystem.h"
#include <map>
#include <set>
#include <algorithm>

int ScoringSystem::calculateScore(HandRank rank, const std::vector<Card> &cards)
{
    // Helper: get card value
    auto cardValue = [](Rank r)
    {
        if (r == Rank::Ace)
            return 11;
        if (r == Rank::King || r == Rank::Queen || r == Rank::Jack)
            return 10;
        return static_cast<int>(r);
    };

    int valueSum = 0;
    for (const auto &c : cards)
        valueSum += cardValue(c.getRank());

    switch (rank)
    {
    case HandRank::HighCard:
        return (5 + valueSum) * 1;
    case HandRank::OnePair:
        return (10 + valueSum) * 2;
    case HandRank::TwoPair:
        return (20 + valueSum) * 2;
    case HandRank::ThreeOfAKind:
        return (30 + valueSum) * 3;
    case HandRank::Straight:
        return (30 + valueSum) * 4;
    case HandRank::Flush:
        return (35 + valueSum) * 4;
    case HandRank::FullHouse:
        return (40 + valueSum) * 4;
    case HandRank::FourOfAKind:
        return (60 + valueSum) * 7;
    case HandRank::StraightFlush:
        return (100 + valueSum) * 8;
    case HandRank::FiveOfAKind:
        return (120 + valueSum) * 12;
    case HandRank::FlushHouse:
        return (140 + valueSum) * 14;
    case HandRank::FlushFive:
        return (160 + valueSum) * 16;
    }
    return 0;
}

HandRank ScoringSystem::evaluate(
    const std::vector<Card> &cards)
{
    std::map<Rank, int> rankCount;
    std::map<Suit, int> suitCount;

    for (const auto &c : cards)
    {
        rankCount[c.getRank()]++;
        suitCount[c.getSuit()]++;
    }

    int pairs = 0;
    bool three = false;
    bool four = false;

    for (auto &r : rankCount)
    {
        if (r.second == 2)
            pairs++;
        if (r.second == 3)
            three = true;
        if (r.second == 4)
            four = true;
    }

    //--------------------------------
    // Flush
    //--------------------------------
    bool flush = false;
    if (cards.size() >= 5)
    {
        for (auto &s : suitCount)
            if (s.second == cards.size())
                flush = true;
    }

    //--------------------------------
    // Straight
    //--------------------------------
    std::vector<int> values;

    for (auto &r : rankCount)
        values.push_back((int)r.first);

    std::sort(values.begin(), values.end());

    bool straight = false;

    if (values.size() >= 5)
    {
        int consecutive = 1;

        for (size_t i = 1; i < values.size(); i++)
        {
            if (values[i] == values[i - 1] + 1)
            {
                consecutive++;

                if (consecutive >= 5)
                {
                    straight = true;
                    break;
                }
            }
            else
            {
                consecutive = 1;
            }
        }
    }

    //--------------------------------
    // Ranking Priority
    //--------------------------------
    if (straight && flush)
        return HandRank::StraightFlush;

    if (four)
        return HandRank::FourOfAKind;

    if (three && pairs == 1)
        return HandRank::FullHouse;

    if (flush)
        return HandRank::Flush;

    if (straight)
        return HandRank::Straight;

    if (three)
        return HandRank::ThreeOfAKind;

    if (pairs == 2)
        return HandRank::TwoPair;

    if (pairs == 1)
        return HandRank::OnePair;

    return HandRank::HighCard;
}

std::string
ScoringSystem::rankToString(HandRank rank)
{
    switch (rank)
    {
    case HandRank::HighCard:
        return "High Card";

    case HandRank::OnePair:
        return "One Pair";

    case HandRank::TwoPair:
        return "Two Pair";

    case HandRank::ThreeOfAKind:
        return "Three of a Kind";

    case HandRank::Straight:
        return "Straight";

    case HandRank::Flush:
        return "Flush";

    case HandRank::FullHouse:
        return "Full House";

    case HandRank::FourOfAKind:
        return "Four of a Kind";

    case HandRank::StraightFlush:
        return "Straight Flush";
    }

    return "";
}