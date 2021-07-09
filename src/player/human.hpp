#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "../move.hpp"
#include "player.hpp"

class Human : public Player {
    Move get_move(const Game &);
    void print_player_type();
};


#endif