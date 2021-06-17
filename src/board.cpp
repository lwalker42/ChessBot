#include <string>
#include <iostream>
#include <algorithm>

#include "piece.hpp"
#include "piece_util.hpp"
#include "move.hpp"
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
    return board[p.first][p.second];
}

std::string Board::to_string() const {
    std::string str;
    for(int i = 0; i < BOARD_SIZE; i++) {
        str+= " ";
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


piece_t Board::move_piece(int r1, int c1, int r2, int c2, Special_Move sm, piece_t captured, piece_t promotion) {
    if (!on_board(r1, c1)) return __;   //Initial pos is out of bounds
    piece_t p = board[r1][c1];          //Initial pos is on board
    if (p == __) return p;              //Empty so exit
    board[r1][c1] = __;
    bool col = get_color(p);
    if (!on_board(r2, c2)) return p;    //Target pos is out of bounds

    switch (sm) {
        case EN_PASSANT:
            board[r2][c2] = p;
            board[r2+(col ? 1 : -1)][c2] = __;
            captured = col ? BP : WP;
            break;

        case PROMOTION:
            captured = board[r2][c2];
            board[r2][c2] = promotion;
            break;

        case KINGSIDE:
            board[r1][c1+2] = p;
            board[r1][c1+1] = board[r1][c1+3];
            board[r1][c1+3] = __;
            break;

        case QUEENSIDE:
            board[r1][c1-2] = p;
            board[r1][c1-1] = board[r1][c1-4];
            board[r1][c1-4] = __;
            break;

        case NONE:
        case MOVE_ONLY:
        case PAWN_STARTING:
        case CAPTURE_ONLY:
        default:
            captured = board[r2][c2];
            board[r2][c2] = p;
            break;
    }
    return p;
}

piece_t Board::move_piece(Move m) {
    std::cout << m.to_string() << "\n";
    piece_t piece = move_piece(m.from.first, m.from.second, m.to.first, m.to.second, m.sm, m.captured, m.promotion);
    return piece;
}


moves_t Board::get_moves(int r, int c, Special_Move sm, Pos ep) const {
    diffs2_t m_list = get_moves_lists(r, c, sm);
    moves_t moves = filter_moves_lists(r, c, m_list, sm, ep);
    return moves;
}

moves_t Board::get_moves(Pos p, Special_Move sm, Pos ep) const {
    return get_moves(p.first, p.second, sm, ep);
}


diffs2_t Board::get_moves_lists(int r, int c, Special_Move sm) const {
    if (!on_board(r, c)) return {};
    return get_piece_moves(board[r][c], sm);
}

//Filter collision with other pieces and edge of board
moves_t Board::filter_moves_lists(int r, int c, diffs2_t moves_list, Special_Move sm, Pos ep) const {
    //std::cout << "Starting with move list: " << move::to_string(moves_list);

    if (!on_board(r, c)) return {};
    piece_t p1 = board[r][c];
    if (p1 == __) return {};

    moves_t moves;
    bool capture;
    bool en_passant;
    diffs_t::iterator it;
    for (diffs_t move_list : moves_list) {
        capture = false;                                //reset capture flag
        en_passant = false;                             //reset en passant flag
        for (it = move_list.begin(); it != move_list.end(); it++) {
            int r_move = r + (*it).first;
            int c_move = c + (*it).second;
            if(on_board(r_move, c_move)) {
                piece_t p2 = board[r_move][c_move];
                if(p2 == __) {                          //piece is empty
                    //std::cout << "Empty space\n";
                    if ((sm == CAPTURE_ONLY || sm == EN_PASSANT) && on_board(ep)) {
                        if (r_move == ep.first + (get_color(p1) ? -1 : 1) && c_move == ep.second) {
                            //std::cout << "En passant!\n";
                            it++;
                            en_passant = true;
                            break;
                        }
                    }
                    continue;
                } else if(same_color(p1, p2)) {         //piece color of location is the same
                    //std::cout << "Friendly piece\n";
                    break;
                } else {                                //piece is opposite color: capture (as long as not a pawn)
                    //std::cout << "Enemy piece\n";
                    if (sm != MOVE_ONLY && sm != PAWN_STARTING
                     && sm != KINGSIDE && sm != QUEENSIDE) {
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

        if (sm == CAPTURE_ONLY || sm == EN_PASSANT
         || sm == KINGSIDE || sm == QUEENSIDE) {        //For getting only the last move in a list
            if (en_passant) {
                moves.push_back(Move ({r, c}, (*(--it) + Pos(r, c)), EN_PASSANT));
            } else if (capture) {
                moves.push_back(Move ({r, c}, *(--it) + Pos(r, c)));
            } else if ((sm == KINGSIDE || sm == QUEENSIDE)
                     && move_list.end() == it) {
                moves.push_back(Move ({r, c}, *(--it) + Pos(r, c), sm));
            }
        } else {
            for (auto valid = move_list.begin(); valid != it; valid++) {
                if (sm == PAWN_STARTING && *(valid) == move_list.back()) {
                    moves.push_back(Move ({r, c}, *(valid) + Pos(r, c), PAWN_STARTING));
                } else {
                    moves.push_back(Move ({r, c}, *(valid) + Pos(r, c)));
                }
            }
        }
    }

    if (is_pawn_promotion(r, c, p1)) {
        pieces_t promotions_moves;
        for (Move move : moves) {
            for (piece_t m : promotions[!get_color(p1)]) {
                move.promotion = m;
            }
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
bool Board::check_for_piece(Pos p, std::vector<piece_t> pieces, diffs2_t diffs_lists) const {
    for (diffs_t diffs : diffs_lists) {
        for (Pos m : diffs) {
            if (!on_board(p+m)) break;          //If off board, go to next move list

            piece_t piece = (*this)[p+m];
            if (piece == __) continue;          //Space is empty so keep searching

            for (piece_t check_piece : pieces) {//There's a piece there; see if it's one we're looking for
                if (piece == check_piece) {
                    return true;
                }
            }
            break;                              //There's a different piece there; go to next move list
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
     || check_for_piece(p, {pieces[5]}, pawn_capture_moves[!color]))    //White is true==1 but white index is [0]
        return true;
    return false;
}