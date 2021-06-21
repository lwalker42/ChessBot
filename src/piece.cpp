//#include <iostream>
//#include <string>
#include <algorithm>

#include "piece.hpp"
#include "move.hpp"
#include "piece_util.hpp"
#include "board_constants.hpp"

using namespace std; 

//White > 0; Black < 0; empty == 0
char to_char(piece_t p) {
    if (p == __) return '-';
    else if (p > 0) return p;
    else return tolower(-p);
}

diffs2_t get_piece_moves(piece_t p, Special_Move sm) {
    switch(abs(p)) {
        case WK:
            return get_king_moves(p, sm);
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


diffs2_t get_pawn_moves(piece_t p, Special_Move sm) {
    int color = (p > 0) ? 0 : 1;
    diffs2_t moves;
    switch (sm) {
    case PAWN_STARTING:
        moves = pawn_first_moves[color];
        break;
    case CAPTURE_ONLY:
        moves = pawn_capture_moves[color];
        break;
    default:
        moves = pawn_moves[color];
        break;
    }
    return moves;
}


diffs2_t get_king_moves(piece_t p, Special_Move sm) {
    diffs2_t moves;
    switch (sm) {
    case KINGSIDE:
        moves = kingside_moves;
        break;
    case QUEENSIDE:
        moves = queenside_moves;
        break;
    default:
        moves = king_moves;
        break;
    }
    return moves;
}