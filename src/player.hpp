#pragma once


#include <vector>
#include "move.hpp"

#define HUMAN_PLAYER 0
#define CPU_PLAYER 1


class Player {
    public:
        virtual Move get_move() = 0;
        virtual void print_player_type() = 0;
};

extern std::vector<Player> player_types;

void init_player_types();