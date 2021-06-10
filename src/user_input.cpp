#include <iostream>
#include <algorithm>
#include <string>

#include "user_input.hpp"

Pos_Move get_move(int input_type) {
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

Pos_Move get_cin_input() {
    //awful way to read user input but want to test other parts
    std::string str;
    std::cout << "Input your move: Inital_RowInitial_ColNew_RowNew_Col (no spaces)\n"; 
    std::cin >> str;
    Pos p (str[0] - 48, str[1] - 48);
    return {p, Move(str[2] - 48 - p.r, str[3] - 48 - p.c)};
}