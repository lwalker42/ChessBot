#include "board_constants.hpp"
#include "util.hpp"
#include "type_defs.hpp"
#include "piece.hpp"





bool is_pawn_first(int r, int c, piece_t p) {
    if (!is_pawn(p) || !on_board(r, c)) return false;
    bool color = get_color(p);
    if (color) return r == (BOARD_SIZE - 2);
    else return r == 1;
}

bool is_pawn_first(Pos pos, piece_t p) {
    return is_pawn_first(pos.first, pos.second, p);
}

bool is_pawn_promotion(int r, int c, piece_t p) {
    if (!is_pawn(p) || !on_board(r, c)) return false;
    bool color = get_color(p);
    if (color) return r == 1;
    else return r == (BOARD_SIZE - 2);
}

bool is_pawn_promotion(Pos pos, piece_t p) {
    return is_pawn_promotion(pos.first, pos.second, p);
}

bool is_kingside(int r, int c, piece_t p) {
    if (!is_rook(p) || !on_board(r, c)) return false;
    bool color = get_color(p);
    if (color) return r == (BOARD_SIZE - 1) && c == (BOARD_SIZE - 1);
    else return r == 0 && c == (BOARD_SIZE - 1);
}

bool is_kingside(Pos pos, piece_t p) {
    return is_kingside(pos.first, pos.second, p);
}

bool is_queenside(int r, int c, piece_t p) {
    if (!is_rook(p) || !on_board(r, c)) return false;
    bool color = get_color(p);
    if (color) return r == (BOARD_SIZE - 1) && c == 0;
    else return r == 0 && c == 0;
}

bool is_queenside(Pos pos, piece_t p) {
    return is_queenside(pos.first, pos.second, p);
}

Pos operator+(const Pos &p1, const Pos &p2) {
  return {p1.first + p2.first, p1.second + p2.second};
}