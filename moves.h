#pragma once    // this is so compiler only includes this header file once, 
                // otherwise if we include moves.h first then player.h, player.h 
                // alr includes moves.h so error
#include <string>
 
enum move {
    rock = 0,
    paper,
    scissors,
    lizard,
    spock
};

    // without inline, multiple definitions errors occur bcs this is a header file
//cant use namespace std because of the multiple definitions errors again
// moveName converts enum into string

    inline std::string moveName(move m) {

    switch(m) {
        case rock:     return "Rock";
        case paper:    return "Paper";
        case scissors: return "Scissors";
        case lizard:   return "Lizard";
        case spock:    return "Spock";
        default:       return "Invalid Move";
    }
}

// converts int to moves 
//couldve done move m = (move)3 but explicit typecasting is better & safer

inline move toMove(int n) {
    return static_cast<move>(n);
}

// should i separate class so logic (winning/losing) is in one place only (encapsulation?) - later 

    inline bool beats[5][5] = {
    { false, false, true,  true,  false },  // Rock beats Scissors, Lizard
    { true,  false, false, false, true  },  // Paper beats Rock, Spock
    { false, true,  false, true,  false },  // Scissors beats Paper, Lizard
    { false, true,  false, false, true  },  // Lizard beats Paper, Spock
    { true,  false, true,  false, false },  // Spock beats Rock, Scissors
};
    
    inline int result(move a, move b){
    if(a == b)
        return 0;

    if(beats[a][b])
        return 1;

    return -1;
    }

    inline std::string reason(move winner, move loser) {
    if (winner == rock     && loser == scissors) return "Rock crushes Scissors";
    if (winner == rock     && loser == lizard)   return "Rock crushes Lizard";
    if (winner == paper    && loser == rock)     return "Paper covers Rock";
    if (winner == paper    && loser == spock)    return "Paper disproves Spock";
    if (winner == scissors && loser == paper)    return "Scissors cuts Paper";
    if (winner == scissors && loser == lizard)   return "Scissors decapitates Lizard";
    if (winner == lizard   && loser == paper)    return "Lizard eats Paper";
    if (winner == lizard   && loser == spock)    return "Lizard poisons Spock";
    if (winner == spock    && loser == rock)     return "Spock vaporizes Rock";
    if (winner == spock    && loser == scissors) return "Spock smashes Scissors";
    return "Draw";
}