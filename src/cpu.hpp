#pragma once

#include "move.hpp"
#include "player.hpp"

class CPU : public Player {
    Move get_move();
    void print_player_type();
};

