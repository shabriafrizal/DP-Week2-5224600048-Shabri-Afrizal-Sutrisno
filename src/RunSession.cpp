#include "RunSession.h"

#include <iostream>
#include <sstream>
#include <set>

int RunSession::calculatePlayerScore(const std::vector<Card> &selectedCards,
                                     HandRank rank)
{
    return ScoringSystem::calculateScore(rank, selectedCards);
}

bool RunSession::advanceTarget()
{
    if (targetIndex == 0)
    {
        targetIndex = 1;
        targetScore = 400;
        return true;
    }

    if (targetIndex == 1)
    {
        targetIndex = 2;
        targetScore = 800;
        return true;
    }

    return false;
}

void RunSession::openShopAfterTargetClear()
{
    std::cout << "\nTarget clear reward: +25 cash\n";
    cash += 25;
    ShopSystem::openDebugShop(cash);
}

void RunSession::run()
{
    player.initializeStarterDeck();
    player.drawStartingHand();

    bool running = true;

    while (running)
    {
        std::cout << "Target score: " << targetScore
                  << " | Total score: " << player.getTotalScore()
                  << " | Cash: " << cash << "\n";

        //--------------------------------
        // SHOW HAND
        //--------------------------------
        player.showHand();

        //--------------------------------
        // EXIT IF DECK EMPTY
        //--------------------------------
        if (player.getDeck().empty())
        {
            std::cout << "Deck empty. Game Over.\n";
            break;
        }

        //--------------------------------
        // SELECT ARRAY
        //--------------------------------
        std::vector<int> selection;
        if (!readSelection(selection))
            break; // user typed 'q'

        //--------------------------------
        // REMOVE DUPLICATE INDEXES
        //--------------------------------
        std::set<int> unique(selection.begin(), selection.end());
        selection.assign(unique.begin(), unique.end());

        //--------------------------------
        // VALIDATION
        //--------------------------------
        if (selection.size() < 1 || selection.size() > 5)
        {
            std::cout << "Select between 1 and 5 cards.\n\n";
            continue;
        }

        //--------------------------------
        // INDEX RANGE VALIDATION
        //--------------------------------
        bool valid = true;
        for (int i : selection)
        {
            if (i < 0 || i >= player.handSize())
                valid = false;
        }

        if (!valid)
        {
            std::cout << "Invalid index.\n\n";
            continue;
        }

        //--------------------------------
        // OPTIONS
        //--------------------------------
        std::cout << "\nSelect Options:\n"
                  << "1. Select Card\n"
                  << "2. Discard Card\n"
                  << "3. Quit\n> ";

        int option;
        std::cin >> option;
        if (option == 3)
            break;

        //--------------------------------
        // GET SELECTED CARDS
        //--------------------------------
        auto selected = player.getSelectedCards(selection);

        //--------------------------------
        // DETECT POKER HAND
        //--------------------------------
        HandRank result = ScoringSystem::evaluate(selected);

        std::cout << "\nDetected: "
                  << ScoringSystem::rankToString(result)
                  << "\n";

        //--------------------------------
        // APPLY ACTION
        //--------------------------------
        bool used = (option == 1);

        if (used)
        {
            int gainedScore = calculatePlayerScore(selected, result);
            player.addScore(gainedScore);

            std::cout << "Gained score: " << gainedScore
                      << " | Total score: " << player.getTotalScore() << "\n";
        }

        player.replaceCards(selection, used);

        if (used && player.getTotalScore() >= targetScore)
        {
            std::cout << "Target " << targetScore
                      << " reached. Deck redrawn from start.\n";

            // Shop is only available after completing the target.
            openShopAfterTargetClear();

            player.initializeStarterDeck();
            player.drawStartingHand();

            if (!advanceTarget())
            {
                std::cout << "All targets completed (200 -> 400 -> 800). You win!\n";
                break;
            }

            std::cout << "Next target: " << targetScore << "\n";
            player.resetScore();
        }

        std::cout << "\n";
    }

    std::cout << "Game Ended.\n";
}

bool RunSession::readSelection(std::vector<int> &outSelection)
{
    std::cout << "Select array:\n> ";
    std::string line;
    std::getline(std::cin >> std::ws, line);

    if (line == "q")
        return false;

    std::stringstream ss(line);
    int index;

    while (ss >> index)
        outSelection.push_back(index);

    return true;
}
