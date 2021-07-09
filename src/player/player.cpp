#include "player.hpp"
#include "human.hpp"
#include "cpu.hpp"

std::vector<Player> player_types;

void init_player_types() {
    player_types[HUMAN_PLAYER] = Human();
    player_types[CPU_PLAYER] = CPU();
}