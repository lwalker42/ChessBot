#include <string>
#include <iostream>
#include <algorithm>

#include "piece.hpp"
#include "piece_util.hpp"
#include "pos.hpp"
#include "move.hpp"
#include "pos_move.hpp"
#include "board_constants.hpp"
#include "board.hpp"
#include "util.hpp"


Board::Board() {
    board = init_board;
}

Board::Board(board_t b) {
    board = b;
}

Board::Board(Board &b) {
    board = b.board;
}

piece_t Board::operator[](Pos p) const {
    return board[p.r][p.c];
}

std::string Board::to_string() const {
    std::string str;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            str += to_char(board[i][j]);
        }
        str += "\n";
    }
    return str;
}

board_t Board::get_board() const {
    return board;
}


piece_t Board::move_piece(int r1, int c1, int r2, int c2, piece_t new_p) {
    if (!on_board(r1, c1)) return __;   //Initial pos is out of bounds

    piece_t p = board[r1][c1];          //Initial pos is on board so move it to...
    if (p == __) return p;
    board[r1][c1] = __;

    if (on_board(r2, c2)) {             //If 2nd pos is on board move it there
        p = (new_p == __) ? p : new_p;  //If a new piece is specified, replace it (promotion)
        board[r2][c2] = p;
    }
    return p;
}

piece_t Board::move_piece(int r, int c, Move m) {
    return move_piece(r, c, r + m.r, c + m.c, m.new_piece);
}

piece_t Board::move_piece(Pos p, int r, int c) {
    return move_piece(p.r, p.c, p.r + r, p.c + c);
}

piece_t Board::move_piece(Pos p, Move m) {
    return move_piece(p.r, p.c, p.r + m.r, p.c + m.c, m.new_piece);
}

piece_t Board::move_piece(Pos_Move pm) {
    piece_t piece = move_piece(pm.pos.r, pm.pos.c, pm.move.r, pm.move.c, pm.move.new_piece);
    if (pm.next) move_piece(*(pm.next));
    return piece;
}


pos_moves_t Board::get_moves(int r, int c, Special_Move sm) const {
    moves2_t m_list = get_moves_lists(r, c, sm);
    pos_moves_t moves = filter_moves_lists(r, c, m_list, sm);
    return moves;
}

pos_moves_t Board::get_moves(Pos p, Special_Move sm) const {
    return get_moves(p.r, p.c, sm);
}


moves2_t Board::get_moves_lists(int r, int c, Special_Move sm) const {
    if (!on_board(r, c)) return {};
    return get_piece_moves(board[r][c], sm);
}

//Filter collision with other pieces and edge of board
pos_moves_t Board::filter_moves_lists(int r, int c, moves2_t moves_list, Special_Move sm) const {
    //std::cout << "Starting with move list: " << move::to_string(moves_list);

    if (!on_board(r, c)) return {};
    piece_t p1 = board[r][c];
    if (p1 == __) return {};

    pos_moves_t moves;
    bool capture;
    moves_t::iterator it;
    for (moves_t move_list : moves_list) {
        capture = false;                                //reset capture flag
        for (it = move_list.begin(); it != move_list.end(); it++) {
            int r_move = r + (*it).r;
            int c_move = c + (*it).c;
            if(on_board(r_move, c_move)) {
                piece_t p2 = board[r_move][c_move];
                if(p2 == __) {                          //piece is empty
                    //std::cout << "Empty space\n";
                    continue;
                } else if(same_color(p1, p2)) {         //piece color of location is the same
                    //std::cout << "Friendly piece\n";
                    break;
                } else {                                //piece is opposite color: capture (as long as not a pawn)
                    //std::cout << "Enemy piece\n";
                    if (sm != MOVE_ONLY && sm != PAWN_STARTING) {
                        it++;
                        capture = true;
                    }
                    break;
                }
            } else {                                    //out of bounds
                //std::cout << "Out of bounds\n";
                break;
            }
        }
        if (sm == CAPTURE_ONLY) {
            if (capture) moves.push_back(Pos_Move(Pos(r, c), *(it-1)));
            continue;
        } else {
            std::transform(move_list.begin(), it, moves.end(), //Convert move to pos_move
            [r, c](Move m) -> Pos_Move {return Pos_Move(Pos(r, c), m);});
        }
        
    }
    return moves;
}

Pos Board::get_king_pos(bool color) const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == (color ? WK : BK))
                return Pos(i, j);
        }
    }
    return Pos(-1, -1);
}

//in_check helper
bool Board::check_for_piece(Pos p, std::vector<piece_t> pieces, moves2_t moves_lists) const {
    for (moves_t moves : moves_lists) {
        for (Move m : moves) {
            if (!on_board(p+m)) break;          //If off board, go to next move list

            piece_t piece = (*this)[p+m];
            if (piece == __) continue;          //Space is empty so keep searching

            for (piece_t check_piece : pieces) {//There's a piece there; see if it's one we're looking for
                if (piece == check_piece) {
                    return true;
                }
                break;                          //There's a different piece there; go to next move list
            }
        }
    }
    return false;
}

bool Board::in_check(bool color) const {
    Pos p = get_king_pos(color);
    if (!on_board(p)) return false;

    std::vector<piece_t> pieces;
    if (color) pieces = {BQ, BR, BB, BN, BK, BP};
    else pieces = {WQ, WR, WB, WN, WK, WP};

    if (check_for_piece(p, {pieces[0], pieces[1]}, rook_moves)
     || check_for_piece(p, {pieces[0], pieces[2]}, bishop_moves)
     || check_for_piece(p, {pieces[3]}, knight_moves)
     || check_for_piece(p, {pieces[4]}, king_moves)
     || check_for_piece(p, {pieces[5]}, pawn_moves[!color]))
        return true;
    return false;
}