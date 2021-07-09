#include "player.hpp"
#include "human.hpp"
#include "cpu.hpp"

p_types player_types;

void init_player_types() {
    player_types.resize(2);

    player_types[HUMAN_PLAYER] = new Human();
    player_types[CPU_PLAYER] = new CPU();
}