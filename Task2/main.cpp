#include <iostream>
#include <string>
#include <vector>

struct GameState
{
    int totalScore = 0;
    int cash = 0;
    int currentTarget = 200;
    int targetIndex = 0;
    int round = 1;
    int maxRounds = 5;
    bool gameOver = false;
};

class PlayerAction
{
public:
    std::vector<int> selectCards() const
    {
        std::cout << "[Phase 1] Player selects cards (placeholder selection).\n";
        return {0, 2, 4};
    }
};

class ScoringSystem
{
public:
    std::string evaluateHand(const std::vector<int> &selection) const
    {
        (void)selection;
        std::cout << "[Phase 2] System evaluates selected cards and detects hand rank.\n";
        return "One Pair";
    }

    int calculateScore(const std::string &handRank) const
    {
        if (handRank == "One Pair")
        {
            return 40;
        }
        return 10;
    }
};

class RewardSystem
{
public:
    void applyRewardOrPenalty(GameState &state, int gainedScore) const
    {
        std::cout << "[Phase 3] Reward/Penalty is applied.\n";
        state.totalScore += gainedScore;

        if (gainedScore > 0)
        {
            state.cash += 5;
        }
    }
};

class RunSession
{
public:
    void startGame()
    {
        std::cout << "=== Task 2 Core Loop Skeleton ===\n";

        while (!isGameOver())
        {
            playerActionPhase();
            systemEvaluationPhase();
            rewardOrPenaltyPhase();
            updateGameStatePhase();
            printRoundSummary();
        }

        std::cout << "Game ended. Final score: " << state.totalScore
                  << " | Cash: " << state.cash << "\n";
    }

private:
    GameState state;
    PlayerAction playerAction;
    ScoringSystem scoringSystem;
    RewardSystem rewardSystem;

    std::vector<int> currentSelection;
    std::string currentHandRank;
    int currentGainedScore = 0;

    bool isGameOver() const
    {
        return state.gameOver;
    }

    void playerActionPhase()
    {
        currentSelection = playerAction.selectCards();
    }

    void systemEvaluationPhase()
    {
        currentHandRank = scoringSystem.evaluateHand(currentSelection);
        currentGainedScore = scoringSystem.calculateScore(currentHandRank);
    }

    void rewardOrPenaltyPhase()
    {
        rewardSystem.applyRewardOrPenalty(state, currentGainedScore);
    }

    void updateGameStatePhase()
    {
        std::cout << "[Phase 4] Game state updates (target progression, round, end check).\n";

        if (state.totalScore >= state.currentTarget)
        {
            ++state.targetIndex;
            state.cash += 25;

            if (state.targetIndex == 1)
            {
                state.currentTarget = 400;
            }
            else if (state.targetIndex == 2)
            {
                state.currentTarget = 800;
            }
            else
            {
                std::cout << "All targets cleared.\n";
                state.gameOver = true;
            }

            state.totalScore = 0;
        }

        ++state.round;
        if (state.round > state.maxRounds)
        {
            std::cout << "Maximum rounds reached.\n";
            state.gameOver = true;
        }
    }

    void printRoundSummary() const
    {
        std::cout << "Round summary -> Hand: " << currentHandRank
                  << " | Gained: " << currentGainedScore
                  << " | Total score: " << state.totalScore
                  << " | Target: " << state.currentTarget
                  << " | Cash: " << state.cash
                  << "\n\n";
    }
};

int main()
{
    RunSession session;
    session.startGame();
    return 0;
}
