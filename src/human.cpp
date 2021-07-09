#include <iostream>
#include <string>

#include "move.hpp"
#include "board_constants.hpp"
#include "human.hpp"

//awful way to read user input but want to test other parts
Move Human::get_move() {
    std::string str;
    std::cout << "Input your move: Inital_Row Initial_Col New_Row New_Col (no spaces)\n"; 
    std::cin >> str;
    if(str.length() > 0 && toupper(str[0]) == 'U') return Move ({'U', -1}, {-1, -1});
    if (str.length() > 2) {
        Move m ({str[0] - 48, str[1] - 48}, {str[2]-48, str[3]-48});
        if (str.length() > 4) {
            m.promotion = (piece_t) str[4];
            m.sm = PROMOTION;
        }
        return m;
    } else {
        return Move ({str[0] - 48, str[1] - 48}, {-1, -1});
    }
}

void Human::print_player_type() {
    std::cout << "Human player\n";
}