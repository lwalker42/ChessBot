#include "board_constants.hpp"
#include "util.hpp"
#include "pos.hpp"
#include "piece.hpp"

bool on_board(int r, int c) {
    return (0 <= r && r < BOARD_SIZE && 0 <= c && c < BOARD_SIZE);
}

bool on_board(Pos p) {
    return on_board(p.r, p.c);
}

bool is_pawn_first(int r, int c, piece_t p) {
    if (!is_pawn(p) || !on_board(r, c)) return false;
    bool color = get_color(p);
    if (color) return r == BOARD_SIZE - 2;
    else return r == 1;
}

bool is_pawn_first(Pos pos, piece_t p) {
    return is_pawn_first(pos.r, pos.c, p);
}