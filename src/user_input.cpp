#include <iostream>
#include <algorithm>
#include <string>

#include "move.hpp"
#include "board_constants.hpp"
#include "user_input.hpp"

Move get_input(int input_type) {
    switch (input_type) {
    case CIN_INPUT: {
        return get_cin_input();
        break;
    }
    
    default:
        return Move({-1, -1}, {-1, -1});
        break;
    }
}

//awful way to read user input but want to test other parts
Move get_cin_input() {
    std::string str;
    std::cout << "Input your move: Inital_Row Initial_Col New_Row New_Col (no spaces)\n"; 
    std::cin >> str;
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