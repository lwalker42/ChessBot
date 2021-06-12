#include <iostream>
#include <string>
#include <algorithm>

#include "util.hpp"
#include "piece.hpp"
#include "game.hpp"
#include "user_input.hpp"
#include "pos_move.hpp"

Game::Game() {
    Board board;
    turn = WHITE;
    white_queenside = true;
    white_kingside = true;
    black_queenside = true;
    black_kingside = true;
    finished = false;
}

void Game::print_game() {
    std::cout << std::endl << board.to_string();
    std::cout << (turn ? "White's turn\n" : "Black's turn\n");
}

void Game::play_game() {
    while(!finished) {
        print_game();
        Pos_Move pm = turn ? get_move(CIN_INPUT) : get_move(CIN_INPUT);
        if (!valid_move(pm)) {
            std::cout << "\n\nInvalid move\n";
            continue;
        } else {
            board.move_piece(pm);
            turn = !turn;
        }
    }

}

bool Game::valid_move(Pos_Move pm) {
    Pos p = pm.pos;
    Move m = pm.move;
    if (!on_board(p)) return false;     //Initial piece is on board
    if (!on_board(p + m)) return false; //Target location is on board

    piece_t piece = board[p];
    if (is_empty(piece)) return false;  //Check that piece is non-empty
    if (get_color(piece) != turn) return false; //Check that piece is the current player's piece

    moves_t moves = get_moves(p, piece);
    if (std::find(moves.begin(), moves.end(), m) == moves.end()) return false;  //Check if move is a valid move

    return true;
}


moves_t Game::get_moves(int r, int c, piece_t piece) {
    moves_t moves;
    if (is_pawn_first(r, c, piece)) {
        moves = board.get_moves(r, c, PAWN_STARTING);
    } else if (is_pawn(piece)) {
        moves = board.get_moves(r, c, MOVE_ONLY);
        moves_t moves2 = board.get_moves(r, c, CAPTURE_ONLY);
        moves.insert(moves.end(), moves2.begin(), moves2.end());
    } else {
        moves = board.get_moves(r, c);
    }
    return moves;
}

moves_t Game::get_moves(Pos p, piece_t piece) {
    return get_moves(p.r, p.c, piece);
}