#ifndef GAME_HPP
#define GAME_HPP

#include <utility>

#include "board.hpp"
#include "pos_move.hpp"


class Game {
    private:
        Board board;
        bool turn, white_queenside, white_kingside, black_queenside, black_kingside, finished;

    public:
        Game();
        void print_game();
        void play_game();

        bool valid_move(Pos_Move);
        moves_t get_moves(int, int, piece_t);
        moves_t get_moves(Pos, piece_t);
};

#endif
