#pragma once

#include <vector>
#include <string>
#include "player/Player.h"
#include "ScoringSystem.h"
#include "ShopSystem.h"

// RunSession encapsulates the main game loop and keeps
// main.cpp clean and focused on high‑level coordination.
class RunSession
{
public:
    /// Execute the game until the player quits or the deck is
    /// exhausted.  The method handles all user interaction
    /// and delegates card logic to Player/ScoringSystem.
    void run();

private:
    Player player;
    int cash = 0;

    int targetScore = 200;
    int targetIndex = 0;

    // helper to read a line of indices from the console.  Returns
    // true if the caller should continue running, false if the user
    // requested a quit ('q').
    bool readSelection(std::vector<int> &outSelection);

    int calculatePlayerScore(const std::vector<Card> &selectedCards,
                             HandRank rank);
    bool advanceTarget();
    void openShopAfterTargetClear();
};
