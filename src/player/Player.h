#pragma once
#include "../card/Deck.h"
#include <vector>

class Player
{
private:
    Deck deck;
    std::vector<Card> hand;
    int totalScore = 0;

public:
    void initializeStarterDeck();

    void drawStartingHand(int count = 8);
    int handSize() const;
    std::vector<Card> getSelectedCards(const std::vector<int> &indexes) const;
    void sortHand();
    void showHand() const;

    void replaceCards(const std::vector<int> &indexes,
                      bool used);

    void addScore(int amount);
    int getTotalScore() const;
    void resetScore();

    Deck &getDeck();
};