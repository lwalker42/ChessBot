#ifndef GAME_HPP
#define GAME_HPP

#include <utility>

#include "board.hpp"
#include "move.hpp"
#include "util.hpp"


class Game {
    private:
        Board board;
        int white, black;
        int ply_count;
        std::string PGN;    //Only works properly with normal chess game
        Pos en_passant_pos = {-1, -1}, check_1 = {-1, -1}, check_2 = {-1, -1};
        bool turn, check, white_kingside, white_queenside, black_kingside, black_queenside, finished, en_passant;
        std::vector<Move> game_moves;

        bool try_move_check(const Move&);
        void handle_special(Move&);
        void unhandle_special(Move&);
        std::string add_to_PGN(Move &);


    public:
        bool display;
        Game(int = 0, int = 0, board_t = init_board, bool t = true, bool wk = true, bool wq = true, bool bk = true, bool bq = true);
        void print_game();
        void play_game();
        void make_move(Move&);
        void unmake_move();

        board_t get_board() const;
        bool get_turn() const;
        bool get_check() const;
        bool valid_move(Move&);
        moves_t get_all_moves();
        moves_t get_moves(int, int, piece_t, bool = false, bool = true);
        moves_t get_moves(Pos, piece_t, bool = false, bool = true);
        pos_t get_blocking(Pos p);
        moves_t filter_check(moves_t);
        bool try_castle(bool, Special_Move);
        bool in_checkmate();

        int perft(int);
        void print_PGN() const;
};

#endif
