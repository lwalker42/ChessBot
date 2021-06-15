#ifndef GAME_HPP
#define GAME_HPP

#include <utility>

#include "board.hpp"
#include "pos_move.hpp"


class Game {
    private:
        Board board;
        bool turn, check, white_queenside, white_kingside, black_queenside, black_kingside, finished, display;
        bool try_move_check(Pos_Move);
        void handle_castle(Pos_Move);

    public:
        Game();
        void print_game();
        void play_game();

        bool valid_move(Pos_Move);
        pos_moves_t get_moves(int, int, piece_t);
        pos_moves_t get_moves(Pos, piece_t);
        pos_moves_t filter_check(pos_moves_t);
        bool in_checkmate();
};

#endif
