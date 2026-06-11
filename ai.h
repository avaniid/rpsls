// add 2 counter feature later

#pragma once
#include <cstdlib> 
#include <ctime>
#include "players.h"

class AI : public Player {  // inheritance bcs ai is a player, so it can use all the functions in player class (like recordMove, getHistory)
private:
    int difficulty;  // 1 = easy (random), 2 = hard (adaptive)

    // counterOf[i] = move that beats move i (so counterOf[rock] = paper, counterOf[paper] = scissors)
    // later on i can add 2 counters for each move to make it more unpredictable (eg. rock is beaten by paper and spock, so counterOf[rock] = {paper, spock})
    // Rock(0) beaten by Paper(1), Paper(1) by Scissors(2),
    // Scissors(2) by Rock(0), Lizard(3) by Rock(0), Spock(4) by Paper(1)
    move counterOf[5] = { paper, scissors, rock, rock, paper };

public:
    AI(int diff) : Player("CPU"), difficulty(diff) {
        srand(time(0));  // Seed random once
    }

    // polymorphism used
    // AIs pickMove is different from humans pickMove, so override it
    // easy mode will be random & hard mode will analyze players history & counter accordingly
    move pickMove() override {
        if (difficulty == 1) {
            return toMove(rand() % 5);
        }

        // AI doesnt have the players history directly
        // the game calls setPlayerHistory() before each AI turn
        int mostUsed = 0;
        for (int i = 1; i < 5; i++) {
            if (moveHistory[i] > moveHistory[mostUsed])
                mostUsed = i;
        }

        // if no history yet, pick a random move
        bool allZero = true;
        for (int i = 0; i < 5; i++) if (moveHistory[i] > 0) { allZero = false; break; }
        if (allZero) return toMove(rand() % 5);

        return counterOf[mostUsed];
    }

    // the game will copy humans history into AI so it can analyze it
    void setPlayerHistory(int* history) {
        for (int i = 0; i < 5; i++) moveHistory[i] = history[i];
    }

    void setDifficulty(int d) { difficulty = d; }
};
