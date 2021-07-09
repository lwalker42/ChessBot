#pragma once


#include <vector>
#include "../move.hpp"
#include "../board.hpp"
#include "../game.hpp"

#define HUMAN_PLAYER 0
#define CPU_PLAYER 1

class Player {
    public:
        virtual Move get_move(const Game &b) = 0;
        virtual void print_player_type() = 0;
};

typedef std::vector<Player *> p_types;

extern p_types player_types;

void init_player_types();