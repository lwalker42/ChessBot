#ifndef GAME_HPP
#define GAME_HPP

#include <utility>

#include "board.hpp"
#include "move.hpp"


class Game {
    private:
        Board board;
        Pos en_passant_pos = {-1, -1};
        bool turn, check, white_queenside, white_kingside, black_queenside, black_kingside, finished, display, en_passant;
        moves_t game_moves;
        bool try_move_check(Move);
        void handle_castle(Move);
        void handle_en_passant(Move);

    public:
        Game();
        void print_game();
        void play_game();
        void make_move(Move);

        bool valid_move(Move&);
        moves_t get_moves(int, int, piece_t);
        moves_t get_moves(Pos, piece_t);
        moves_t filter_check(moves_t);
        bool try_castle(bool, Special_Move);
        bool in_checkmate();
};

#endif
