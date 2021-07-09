#pragma once

#include "../piece.hpp"
#include "../move.hpp"
#include "../game.hpp"
#include "player.hpp"

#define P_VAL 1.0
#define N_VAL 3.05
#define B_VAL 3.33
#define R_VAL 5.63
#define Q_VAL 9.5
#define K_VAL 1E4

class CPU : public Player {
    Move get_move(const Game &);
    void print_player_type();
};

Move evaluate_depth(Game &, int);
double evaluate_piece(piece_t);

double evaluate(const Game &);