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
    char c;
    switch (get_piece(p)) {
        case KING:
            c = 'K';
            break;
        case QUEEN:
            c = 'Q';
            break;
        case ROOK:
            c = 'R';
            break;
        case BISHOP:
            c = 'B';
            break;
        case KNIGHT:
            c = 'N';
            break;
        case PAWN:
            c = 'P';
            break;
        default:
            c = '-';
            break;
    }
    if (p & COLOR_MASK) return c;
    else return tolower(c);
}

diffs2_t get_piece_moves(piece_t p, Special_Move sm) {
    switch(get_piece(p)) {
        case KING:
            return get_king_moves(p, sm);
        case QUEEN:
            return queen_moves;
        case ROOK:
            return rook_moves;
        case BISHOP:
            return bishop_moves;
        case KNIGHT:
            return knight_moves;
        case PAWN:
            return get_pawn_moves(p, sm);
        default:
            return {};
    }
}


diffs2_t get_pawn_moves(piece_t p, Special_Move sm) {
    int color = get_color(p) ? 0 : 1;
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