//#include <iostream>
//#include <string>
#include <algorithm>

#include "piece.hpp"
#include "move.hpp"
#include "piece_util.hpp"
#include "pos.hpp"
#include "board_constants.hpp"

using namespace std; 

//White > 0; Black < 0; empty == 0
char to_char(piece_t p) {
    if (p == __) return '-';
    else if (p > 0) return p;
    else return tolower(-p);
}

bool is_empty(piece_t p) {
    return p == __;
}

bool get_color(piece_t p) {
    return p > 0;
}

bool same_color(piece_t p1, piece_t p2) {
    return p1 * p2 > 0;
}

moves2_t get_piece_moves(piece_t p, Special_Move sm) {
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
            return get_pawn_moves(p, sm);
        default:
            return {};
    }
}

moves2_t get_pawn_moves(piece_t p, Special_Move sm) {
    int color = (p > 0) ? 0 : 1;
    moves2_t moves;
    switch (sm) {
    case PAWN_STARTING:
        moves = pawn_first_moves[color];
        break;
    case PAWN_CAPTURE:
        moves = pawn_capture_moves[color];
        break;
    default:
        moves = pawn_moves[color];
        break;
    }
        /*std::for_each(moves.begin(), 
                      moves.end(), 
            [](moves_t &ms) {
                std::for_each(ms.begin(),
                              ms.end(), 
                              [](Move &m){m.r *= -1; m.c *=-1;});
                            });*/ //There's so few pawn moves, 
                                  //it's probably faster to do by hand
    return moves;
}