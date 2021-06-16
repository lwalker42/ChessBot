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
    check = false;
    finished = false;
    en_passant = false;
    white_queenside = true;
    white_kingside = true;
    black_queenside = true;
    black_kingside = true;
    display = true;
}

void Game::print_game() {
    std::cout << std::endl << board.to_string();
    std::cout << (turn ? "White's turn\n" : "Black's turn\n");
    std::cout << (check ? "You are in check!\n" : "");
}

void Game::play_game() {
    while(!finished) {
        if(display) print_game();
        Pos_Move pm = turn ? get_input(CIN_INPUT) : get_input(CIN_INPUT);
        Pos_Move *ptr = valid_move(pm);
        if (!ptr) {
            std::cout << "\n\nInvalid move\n";
            continue;
        }
        handle_castle(pm);
        handle_en_passant(pm);
        board.move_piece(*ptr);
        turn = !turn;
        check = board.in_check(turn);
        if (check) in_checkmate();
    }
    std::cout << "\n" << board.to_string();
    std::cout << "Game over.  " << (turn ? "Black" : "White") << " wins!\n";
}


Pos_Move *Game::valid_move(Pos_Move pm) {
    Pos p = pm.pos;
    Move m = pm.move;
    if (!on_board(p)) return NULL;      //Initial piece is on board
    if (!on_board(p + m)) return NULL;  //Target location is on board

    piece_t piece = board[p];
    if (is_empty(piece)) return NULL;           //Check that piece is non-empty
    if (get_color(piece) != turn) return NULL;  //Check that piece is the current player's piece

    pos_moves_t moves = get_moves(p, piece);
    //for (auto move : moves) std::cout << move.to_string() << "\n";
    auto it = std::find_if(moves.begin(), moves.end(), 
                           [&m](Pos_Move temp) -> bool {return (temp.move) == m;});   //Check if move is a valid move
    Pos_Move *move = (it == moves.end()) ? NULL : new Pos_Move((*it));
    return move;
}


pos_moves_t Game::get_moves(int r, int c, piece_t piece) {
    pos_moves_t moves;

    if (is_pawn(piece)) {                                           //If pawn
        if (is_pawn_first(r, c, piece)) {                           //First get non-capturing moves
            moves = board.get_moves(r, c, PAWN_STARTING);           //Move 1 or 2
        } else {
            moves = board.get_moves(r, c, MOVE_ONLY);               //Move 1
        }
        pos_moves_t moves2 ( en_passant 
                           ? board.get_moves(r, c, CAPTURE_ONLY, en_passant_pos)  
                           : board.get_moves(r, c, CAPTURE_ONLY));   //Then get capturing moves
        moves.insert(moves.end(), moves2.begin(), moves2.end());
                                                                    //TODO Then handle promotion
    } else {
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
    //std::cout << "\n" << move::to_string(moves) << "\n";
    moves.erase(std::remove_if(moves.begin(), 
                               moves.end(), 
                               [this](Pos_Move m){return this->try_move_check(m);}), moves.end());
    
    //std::cout << "\n" << move::to_string(moves) << "\n";
    return moves;
}


bool Game::in_checkmate() {
    board_t b = board.get_board();
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j <BOARD_SIZE; j++) {
            piece_t p = b[i][j];
            if (is_empty(p)) continue;
            if (get_color(p) == turn) {
                if(!get_moves(i, j, p).empty()) return false;
            }
        }
    }
    finished = true;
    return true;
}


void Game::handle_castle(Pos_Move move) {
    piece_t p = board[move.pos];
    bool c = get_color(p);
    if (c ? !white_kingside && !white_queenside
          : !black_kingside && !black_queenside) return;    //If castling ins't possible, skip
          
    if (is_king(p)) {
        if (c) {
            white_kingside = false;
            white_queenside = false;
        } else {
            black_kingside = false;
            black_queenside = false;
        }
    } else if (is_kingside(move.pos, p)) {
        (c ? white_kingside : black_kingside) = false;
    } else if (is_queenside(move.pos, p)) {
        (c ? white_queenside : black_queenside) = false;
    }
}

void Game::handle_en_passant(Pos_Move move) {
    piece_t p = board[move.pos];
    if (is_pawn_first(move.pos, p) && abs(move.move.r) > 1) {
        en_passant = true;
        en_passant_pos = move.pos + move.move;
    } else {
        en_passant = false;
    }
}