#pragma once

#include <iostream>
#include <fstream>
#include "players.h"
#include "ai.h"

// ANSI color codes for output
#define GREEN  "\033[32m"
#define RED    "\033[31m"
#define YELLOW "\033[33m"
#define CYAN   "\033[36m"
#define RESET  "\033[0m"

class Game {
private:
    Player* human;
    AI* cpu;
    int totalRounds;
    int draws;

    void printSeparator() {
        std::cout << CYAN
                  << "\n----------------------------------------\n"
                  << RESET;
    }

    void printResult(move hMove, move cMove) {
        std::cout << "\nYou played:  "
                  << YELLOW << moveName(hMove) << RESET;

        std::cout << "\nCPU played:  "
                  << YELLOW << moveName(cMove) << RESET << "\n";

        int res = result(hMove, cMove);

        if (res == 1) {
            std::cout << GREEN
                      << "You WIN! "
                      << reason(hMove, cMove)
                      << RESET << "\n";

            human->addPoint();
        }
        else if (res == -1) {
            std::cout << RED
                      << "You LOSE. "
                      << reason(cMove, hMove)
                      << RESET << "\n";

            cpu->addPoint();
        }
        else {
            std::cout << YELLOW
                      << "DRAW!"
                      << RESET << "\n";

            draws++;
        }

        totalRounds++;
    }

    void printScoreboard() {
        printSeparator();

        std::cout
            << "SCORE  |  "
            << human->getName()
            << ": "
            << human->getScore()
            << "  |  CPU: "
            << cpu->getScore()
            << "  |  Draws: "
            << draws
            << "\n";

        printSeparator();
    }

    void saveStats() {
        std::ofstream file("stats.txt");

        file << "=== RPSLS Stats ===\n";
        file << "Player: " << human->getName() << "\n";
        file << "Wins: " << human->getScore() << "\n";
        file << "Losses: " << cpu->getScore() << "\n";
        file << "Draws: " << draws << "\n";
        file << "Total Rounds: " << totalRounds << "\n";

        file << "\nYour move breakdown:\n";

        int* h = human->getHistory();

        std::string names[] =
        {
            "Rock",
            "Paper",
            "Scissors",
            "Lizard",
            "Spock"
        };

        for (int i = 0; i < 5; i++)
        {
            file << "  "
                 << names[i]
                 << ": "
                 << h[i]
                 << " times\n";
        }

        file.close();

        std::cout << CYAN
                  << "\nStats saved to stats.txt!\n"
                  << RESET;
    }

public:
    Game()
        : totalRounds(0),
          draws(0)
    {
        std::string pname;

        std::cout
            << CYAN
            << "=== Rock Paper Scissors Lizard Spock ===\n"
            << RESET;

        std::cout << "Enter your name: ";
        std::cin >> pname;

        int diff;

        std::cout
            << "Difficulty: 1 = Easy (random)  2 = Hard (adaptive AI)\n> ";

        std::cin >> diff;

        while (diff != 1 && diff != 2)
        {
            std::cout << "Enter 1 or 2: ";
            std::cin >> diff;
        }

        human = new Player(pname);
        cpu = new AI(diff);
    }

    void run() {
        char again = 'y';

        while (again == 'y' || again == 'Y')
        {
            printSeparator();

            cpu->setPlayerHistory(human->getHistory());

            move hMove = human->pickMove();
            move cMove = cpu->pickMove();

            human->recordMove(hMove);
            cpu->recordMove(cMove);

            printResult(hMove, cMove);

            printScoreboard();

            std::cout << "\nPlay again? (y/n): ";
            std::cin >> again;
        }

        printSeparator();

        std::cout << "\n=== FINAL SCORE ===\n";

        std::cout
            << human->getName()
            << ": "
            << human->getScore()
            << "\n";

        std::cout
            << "CPU: "
            << cpu->getScore()
            << "\n";

        std::cout
            << "Draws: "
            << draws
            << "\n";

        if (human->getScore() > cpu->getScore())
        {
            std::cout
                << GREEN
                << "\nYou win overall!\n"
                << RESET;
        }
        else if (cpu->getScore() > human->getScore())
        {
            std::cout
                << RED
                << "\nCPU wins overall. Better luck next time!\n"
                << RESET;
        }
        else
        {
            std::cout
                << YELLOW
                << "\nOverall Draw!\n"
                << RESET;
        }

        saveStats();
    }

    ~Game() {
        delete human;
        delete cpu;
    }
};