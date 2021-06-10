#include "board_constants.hpp"
#include "util.hpp"
#include "pos.hpp"

bool on_board(int r, int c) {
    return (0 <= r && r < BOARD_SIZE && 0 <= c && c < BOARD_SIZE);
}

bool on_board(Pos p) {
    return on_board(p.r, p.c);
}