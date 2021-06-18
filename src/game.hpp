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
        std::vector<Move> game_moves;
        bool try_move_check(const Move&);
        void handle_special(Move&);
        void unhandle_special(Move&);

    public:
        Game();
        Game(board_t);
        Game(bool);
        void print_game();
        void play_game();
        void make_move(Move&);
        Move unmake_move();

        bool valid_move(Move&);
        moves_t get_all_moves();
        moves_t get_moves(int, int, piece_t);
        moves_t get_moves(Pos, piece_t);
        moves_t filter_check(moves_t);
        bool try_castle(bool, Special_Move);
        bool in_checkmate();

        int perft(int);
};

#endif
