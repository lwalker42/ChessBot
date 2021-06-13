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
    if (color) return r == (BOARD_SIZE - 2);
    else return r == 1;
}

bool is_pawn_first(Pos pos, piece_t p) {
    return is_pawn_first(pos.r, pos.c, p);
}

bool is_pawn_promotion(int r, int c, piece_t p) {
    if (!is_pawn(p) || !on_board(r, c)) return false;
    bool color = get_color(p);
    if (color) return r == 1;
    else return r == (BOARD_SIZE - 2);
}

bool is_pawn_promotion(Pos pos, piece_t p) {
    return is_pawn_promotion(pos.r, pos.c, p);
}

bool is_kingside(int r, int c, piece_t p) {
    if (!is_rook(p) || !on_board(r, c)) return false;
    bool color = get_color(p);
    if (color) return r == (BOARD_SIZE - 1) && c == (BOARD_SIZE - 1);
    else return r == 0 && c == (BOARD_SIZE - 1);
}

bool is_kingside(Pos pos, piece_t p) {
    return is_kingside(pos.r, pos.c, p);
}

bool is_queenside(int r, int c, piece_t p) {
    if (!is_rook(p) || !on_board(r, c)) return false;
    bool color = get_color(p);
    if (color) return r == (BOARD_SIZE - 1) && c == 0;
    else return r == 0 && c == 0;
}

bool is_queenside(Pos pos, piece_t p) {
    return is_queenside(pos.r, pos.c, p);
}