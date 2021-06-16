#ifndef GAME_HPP
#define GAME_HPP

#include <utility>

#include "board.hpp"
#include "pos_move.hpp"
#include "pos.hpp"


class Game {
    private:
        Board board;
        Pos en_passant_pos = {-1, -1};
        bool turn, check, white_queenside, white_kingside, black_queenside, black_kingside, finished, display, en_passant;
        bool try_move_check(Pos_Move);
        void handle_castle(Pos_Move);
        void handle_en_passant(Pos_Move);

    public:
        Game();
        void print_game();
        void play_game();

        Pos_Move *valid_move(Pos_Move);
        pos_moves_t get_moves(int, int, piece_t);
        pos_moves_t get_moves(Pos, piece_t);
        pos_moves_t filter_check(pos_moves_t);
        bool try_castle(bool, Special_Move);
        bool in_checkmate();
};

#endif
