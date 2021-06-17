#include <iostream>
#include <string>
#include <algorithm>

#include "util.hpp"
#include "piece.hpp"
#include "game.hpp"
#include "user_input.hpp"
#include "move.hpp"
#include "board_constants.hpp"

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
        Move m = turn ? get_input(CIN_INPUT) : get_input(CIN_INPUT);
        if (!valid_move(m)) {
            std::cout << "\n\nInvalid move\n";
            continue;
        }
        handle_castle(m);
        handle_en_passant(m);
        board.move_piece(m);
        turn = !turn;
        check = board.in_check(turn);
        if (check) in_checkmate();
    }
    std::cout << "\n" << board.to_string();
    std::cout << "Game over.  " << (turn ? "Black" : "White") << " wins!\n";
}

void Game::make_move(Move m) {

}


bool Game::valid_move(Move &m) {
    if (!on_board(m.from)) return NULL;      //Initial piece is on board
    if (!on_board(m.to)) return NULL;  //Target location is on board

    piece_t piece = board[m.from];
    if (is_empty(piece)) return NULL;           //Check that piece is non-empty
    if (get_color(piece) != turn) return NULL;  //Check that piece is the current player's piece

    moves_t moves = get_moves(m.from, piece);
    //for (auto move : moves) std::cout << move.to_string() << "\n";
    auto it = std::find_if(moves.begin(), moves.end(), 
                           [&m](Move move) -> bool {return m.to == move.to
                                                        && (m.promotion == __ || m.promotion == abs(move.promotion));});  //Check if move is a valid move
    if (it == moves.end()) {
        return false;
    } else {
        m = *it;
        return true;
    }
}


moves_t Game::get_moves(int r, int c, piece_t piece) {
    moves_t moves;

    if (is_pawn(piece)) {                                           //If pawn
        if (is_pawn_first(r, c, piece)) {                           //First get non-capturing moves
            moves = board.get_moves(r, c, PAWN_STARTING);           //Move 1 or 2
        } else {
            moves = board.get_moves(r, c, MOVE_ONLY);               //Move 1
        }
        moves_t moves2 ( en_passant 
                           ? board.get_moves(r, c, CAPTURE_ONLY, en_passant_pos)  
                           : board.get_moves(r, c, CAPTURE_ONLY));   //Then get capturing moves
        moves.insert(moves.end(), moves2.begin(), moves2.end());
                                                                    //TODO Then handle promotion
    } else if(is_king(piece)) {
        moves = board.get_moves(r, c);
        bool col = get_color(piece);
        moves_t kings = board.get_moves(r, c, KINGSIDE);
        moves_t queens = board.get_moves(r, c, QUEENSIDE);
        if (try_castle(col, KINGSIDE) && kings.size() > 0) moves.push_back(kings[0]);
        if (try_castle(col, QUEENSIDE) && queens.size() > 0) moves.push_back(queens[0]);
    } else {
        moves = board.get_moves(r, c);
    }
    return filter_check(moves);
}

moves_t Game::get_moves(Pos p, piece_t piece) {
    return get_moves(p.first, p.second, piece);
}


//filter_check helper: remove if move puts current player in check
bool Game::try_move_check(Move move) {
    Board b(board);
    b.move_piece(move);
    return b.in_check(turn);
}

moves_t Game::filter_check(moves_t moves) {
    //std::cout << "\n" << move::to_string(moves) << "\n";
    moves.erase(std::remove_if(moves.begin(), 
                               moves.end(), 
                               [this](Move m){return this->try_move_check(m);}), moves.end());
    
    //std::cout << "\n" << move::to_string(moves) << "\n";
    return moves;
}


bool Game::try_castle(bool color, Special_Move side) {
    if (board.in_check(color)) return false;
    board_t b = board.get_board();
    if (side == KINGSIDE) {
        //std::cout << "Trying kingside\n";
        return (color ? white_kingside : black_kingside)
            && !try_move_check(kingside[!color][0])
            && !try_move_check(kingside[!color][1]);
    } else {
        //std::cout << "Trying queenside\n";
        return (color ? white_queenside : black_queenside)
            && !try_move_check(queenside[!color][0])
            && !try_move_check(queenside[!color][1]);
    }
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


void Game::handle_castle(Move move) {
    piece_t p = board[move.from];
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
    } else if (is_kingside(move.from, p)) {
        (c ? white_kingside : black_kingside) = false;
    } else if (is_queenside(move.from, p)) {
        (c ? white_queenside : black_queenside) = false;
    }
}

void Game::handle_en_passant(Move move) {
    if (move.sm == PAWN_STARTING) {
        en_passant = true;
        en_passant_pos = move.to;
    } else {
        en_passant = false;
    }
}