#include "board.h"
#include "util.h"

bool on_board(int r, int c) {
    return (0 <= r && r < BOARD_SIZE && 0 <= c && c < BOARD_SIZE);
}