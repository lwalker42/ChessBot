//#include <iostream>
//#include <string>
#include <cctype>

#include "piece.hpp"
#include "board_constants.hpp"

using namespace std; 

//White > 0; Black < 0; empty == 0
char to_char(piece_t p) {
    if (p == __) return '-';
    else if (p > 0) return p;
    else return -p;
}

bool same_color(piece_t p1, piece_t p2) {
    return p1 * p2 > 0;
}

moves2_t get_piece_moves(piece_t p) {
    switch(abs(p)) {
        case WK:
            return king_moves;
        case WQ:
            return queen_moves;
        case WR:
            return rook_moves;
        case WB:
            return bishop_moves;
        case WN:
            return knight_moves;
        case WP:
            return pawn_moves;
        default:
            return {};
    }
}