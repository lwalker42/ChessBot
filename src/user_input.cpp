#include <iostream>
#include <algorithm>
#include <string>

#include "user_input.hpp"

Pos_Move get_input(int input_type) {
    switch (input_type) {
    case CIN_INPUT: {
        return get_cin_input();
        break;
    }
    
    default:
        return {Pos(-1, -1), Move(0, 0)};
        break;
    }
}

//awful way to read user input but want to test other parts
Pos_Move get_cin_input() {
    std::string str;
    std::cout << "Input your move: Inital_Row Initial_Col New_Row New_Col (no spaces)\n"; 
    std::cin >> str;
    Pos p (str[0] - 48, str[1] - 48);
    if (str.length() > 2) {
        Pos_Move pm = {p, Move(str[2]-48-p.r, str[3]-48-p.c)};
        if (str.length() > 4) pm.move.new_piece = (piece_t) str[4];
        return pm;
    } else {
        return {p, Move(0, 0)};     //See moves for a piece
    }
}