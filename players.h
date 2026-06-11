// ai can use the move history to predict humans next move and choose a counter move accordingly
// so later on rmb to add a move history function to the player class that logs what move was made after every round
#pragma once
#include <string>
#include "moves.h"
#include <iostream>

class Player {
protected:
    std::string name;
    int score;
    int moveHistory[5];  
    // moveHistory = how many times the move was played, i = 5 as there are 5 moves

public:
    Player(std::string n) : name(n), score(0) {
        for (int i = 0; i < 5; i++) moveHistory[i] = 0;
    }

    // this func is called after every round to log whatever move was made
    void recordMove(move m) {
        moveHistory[m]++;
    }

    void addPoint() { score++; }
    int getScore() { return score; }
    std::string getName() { return name; }
    int* getHistory() { return moveHistory; }

    // asks human to pick a move 
    virtual move pickMove() {
        std::cout << "\nyour move:\n";
        std::cout << "  0 = rock\n  1 = paper\n  2 = scissors\n  3 = lizard\n  4 = spock\n";
        std::cout << "> ";
        int choice;
        std::cin >> choice;
        while (choice < 0 || choice > 4) {
            std::cout << "invalid. enter a number from 0-4: ";
            std::cin >> choice;
        }
        return toMove(choice);
    }

    virtual ~Player() {}
};
