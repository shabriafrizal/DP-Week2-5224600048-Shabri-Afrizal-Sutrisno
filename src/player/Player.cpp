#include "Player.h"
#include <iostream>
#include <algorithm>

void Player::initializeStarterDeck()
{
    deck.createStarterDeck();
    deck.shuffle();
}

void Player::addScore(int amount)
{
    totalScore += amount;
}

int Player::getTotalScore() const
{
    return totalScore;
}

void Player::resetScore()
{
    totalScore = 0;
}

Deck &Player::getDeck()
{
    return deck;
}

void Player::drawStartingHand(int count)
{
    hand.clear();

    for (int i = 0; i < count; i++)
        hand.push_back(deck.draw());

    sortHand();
}

int Player::handSize() const
{
    return hand.size();
}

void Player::showHand() const
{
    std::cout << "Deck remaining: " << deck.size() << "\n";
    std::cout << "==== HAND ====\n";

    if (hand.empty())
    {
        std::cout << "(empty)\n\n";
        return;
    }

    Rank currentRank = hand[0].getRank();

    for (size_t i = 0; i < hand.size(); i++)
    {
        // new rank group
        if (i != 0 &&
            hand[i].getRank() != currentRank)
        {
            std::cout << "| ";
            currentRank = hand[i].getRank();
        }

        std::cout << hand[i].toString() << " ";
    }

    std::cout << "\n\n";
}

void Player::replaceCards(const std::vector<int> &indexes,
                          bool used)
{
    std::vector<int> sorted = indexes;

    // remove safely
    std::sort(sorted.rbegin(), sorted.rend());

    for (int i : sorted)
    {
        if (used)
            std::cout << hand[i].toString()
                      << " ";
        else
            std::cout << hand[i].toString()
                      << " ";

        hand.erase(hand.begin() + i);
    }
    std::cout << "\n";

    // draw back to 8 cards
    while (hand.size() < 8 && !deck.empty())
        hand.push_back(deck.draw());

    sortHand();
}

void Player::sortHand()
{
    std::sort(hand.begin(), hand.end());
}

std::vector<Card>
Player::getSelectedCards(
    const std::vector<int> &indexes) const
{
    std::vector<Card> selected;

    for (int i : indexes)
        selected.push_back(hand[i]);

    return selected;
}