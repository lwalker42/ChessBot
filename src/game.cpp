#include <iostream>
#include <string>
#include <algorithm>

#include "util.hpp"
#include "piece.hpp"
#include "game.hpp"
#include "user_input.hpp"
#include "pos_move.hpp"
#include "move.hpp"

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

    pos_moves_t moves = get_moves(p, piece);
    return std::any_of(moves.begin(), moves.end(), 
           [&m](Pos_Move temp) -> bool {return temp.move == m;});   //Check if move is a valid move
}


pos_moves_t Game::get_moves(int r, int c, piece_t piece) {
    pos_moves_t moves;

    if (is_pawn(piece)) {                                           //If pawn
        if (is_pawn_first(r, c, piece)) {                                  //First get non-capturing moves
            moves = board.get_moves(r, c, PAWN_STARTING);           //Move 1 or 2
        } else {
            moves = board.get_moves(r, c, MOVE_ONLY);               //Move 1
        }
        pos_moves_t moves2 = board.get_moves(r, c, CAPTURE_ONLY);   //Then get capturing moves
        moves.insert(moves.end(), moves2.begin(), moves2.end());    //TODO Then handle promotion
    }                                                               //TODO case on king and rook for castling
    else {
        moves = board.get_moves(r, c);
    }

    return filter_check(moves);
}

pos_moves_t Game::get_moves(Pos p, piece_t piece) {
    return get_moves(p.r, p.c, piece);
}


//filter_check helper: remove if move puts current player in check
bool Game::try_move_check(Pos_Move move) {
    Board b(board);
    b.move_piece(move);
    return b.in_check(turn);
}

pos_moves_t Game::filter_check(pos_moves_t moves) {
    std::cout << "\n" << move::to_string(moves) << "\n";
    moves.erase(std::remove_if(moves.begin(), 
                               moves.end(), 
                               [this](Pos_Move m){return this->try_move_check(m);}), moves.end());
    
    std::cout << "\n" << move::to_string(moves) << "\n";
    return moves;
}