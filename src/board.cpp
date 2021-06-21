#include <string>
#include <iostream>
#include <algorithm>

#include "piece.hpp"
#include "piece_util.hpp"
#include "move.hpp"
#include "board_constants.hpp"
#include "board.hpp"
#include "util.hpp"
#include "timer.hpp"


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
    Move m ({r1, c1}, {r2, c2}, sm, captured, promotion);
    return move_piece(m);
}

piece_t Board::move_piece(const Move &m) {
    //std::cout << m.to_string() << "\n";
    int r1 = m.from.first, c1 = m.from.second, r2 = m.to.first, c2 = m.to.second;
    //if (!on_board(r1, c1)) return __;   //Initial pos is out of bounds
    piece_t p = board[r1][c1];          //Initial pos is on board
    //if (p == __) return p;              //Empty so exit
    board[r1][c1] = __;
    bool col = get_color(p);
    //if (!on_board(r2, c2)) return p;    //Target pos is out of bounds

    switch (m.sm) {
        case EN_PASSANT:
            board[r2][c2] = p;
            board[r2+(col ? 1 : -1)][c2] = __;
            break;

        case PROMOTION:
            board[r2][c2] = m.promotion;
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
            board[r2][c2] = p;
            break;
    }
    return p;
}


//Only guranteed to work for the previous move
piece_t Board::unmove_piece(int r1, int c1, int r2, int c2, Special_Move sm, piece_t captured, piece_t promotion) {
    Move m ({r1, c1}, {r2, c2}, sm, captured, promotion);
    return move_piece(m);
}

piece_t Board::unmove_piece(const Move &m) {
    //std::cout << m.to_string() << "\n";
    int r1 = m.from.first, c1 = m.from.second, r2 = m.to.first, c2 = m.to.second;
    piece_t p = board[r2][c2];          //Initial pos is on board
    board[r2][c2] = __;
    bool col = get_color(p);

    switch (m.sm) {
        case EN_PASSANT:
            board[r1][c1] = p;
            board[r2+(col ? 1 : -1)][c2] = m.captured;
            break;

        case PROMOTION:
            board[r1][c1] = col ? WP : BP;
            board[r2][c2] = m.captured;
            break;

        case KINGSIDE:
            board[r1][c1] = p;
            board[r1][c1+3] = board[r1][c1+1];
            board[r1][c1+1] = __;
            break;

        case QUEENSIDE:
            board[r1][c1] = p;
            board[r1][c1-4] = board[r1][c1-1];
            board[r1][c1-1] = __;
            break;

        case NONE:
        case MOVE_ONLY:
        case PAWN_STARTING:
        case CAPTURE_ONLY:
        default:
            board[r2][c2] = m.captured;
            board[r1][c1] = p;
            break;
    }
    return p;
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

    //std::cout << "piece " << (char)board[r][c] << " at (" << r << ", " << c <<")\n";

    if (!on_board(r, c)) return {};
    piece_t p1 = board[r][c];
    if (p1 == __) return {};

    moves_t moves;
    bool capture;
    bool en_passant;
    int r_move, c_move;
    diffs_t::iterator it;
    for (diffs_t move_list : moves_list) {
        capture = false;                                //reset capture flag
        en_passant = false;                             //reset en passant flag
        for (it = move_list.begin(); it != move_list.end(); it++) {
            r_move = r + (*it).first;
            c_move = c + (*it).second;
            if(on_board(r_move, c_move)) {
                piece_t p2 = board[r_move][c_move];
                if(p2 == __) {                          //piece is empty
                    //std::cout << "Empty space\n";
                    if (is_pawn(p1) && (sm == CAPTURE_ONLY || sm == EN_PASSANT) && on_board(ep)) {
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
            Pos to = (*(std::prev(it)) + Pos(r, c));
            if (en_passant) {
                moves.push_back(Move ({r, c}, to, EN_PASSANT, (*this)[ep]));
            } else if (capture) {
                moves.push_back(Move ({r, c}, to, sm, (*this)[to]));
            } else if ((sm == KINGSIDE || sm == QUEENSIDE)
                     && move_list.end() == it) {
                moves.push_back(Move ({r, c}, to, sm));
            }
        } else {
            for (auto valid = move_list.begin(); valid != it; valid++) {
                Pos to = *(valid) + Pos(r, c);
                if (sm == PAWN_STARTING && *(valid) == move_list.back()) {
                    moves.push_back(Move ({r, c}, to, PAWN_STARTING));      //For en passant handling
                } else {
                    moves.push_back(Move ({r, c}, to, NONE, (*this)[to]));
                }
            }
        }
    }

    if (is_pawn_promotion(r, c, p1)) {
        moves_t old_moves = moves;
        moves.clear();
        for (Move move : old_moves) {
            for (piece_t p : promotions[!get_color(p1)]) {
                Move m (move);
                m.sm = PROMOTION;
                m.promotion = p;
                moves.push_back(m);
            }
        }
    }
    //std::cout << "Ending with move list: " << move::to_string(moves) << "\n";
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
bool Board::check_for_piece(Pos p, std::vector<piece_t> pieces, diffs2_t diffs_lists, Pos &check_pos) const {
    int r = 0;
    int c = 0;
    diffs_t::iterator it;
    for (auto d_it = diffs_lists.begin(); d_it != diffs_lists.end(); d_it++) {
        for (it = (*d_it).begin(); it != (*d_it).end(); it++) {
            r = p.first + (*it).first;
            c = p.second + (*it).second;
            if (!on_board(r, c)) break;          //If off board, go to next move list

            //piece_t piece = board[r][c];
            if (board[r][c] == __) continue;          //Space is empty so keep searching

            for (piece_t check_piece : pieces) {//There's a piece there; see if it's one we're looking for
                if (board[r][c] == check_piece) {
                    check_pos.first = r;
                    check_pos.second = c;
                    return true;
                }
            }
            break;                              //There's a different piece there; go to next move list
        }
    }
    return false;
}


bool Board::check_for_piece(Pos p, std::vector<piece_t> pieces, diffs2_t diffs_lists) const {
    Pos check_pos(-1, -1);
    return check_for_piece(p, pieces, diffs_lists, check_pos);
}


bool Board::in_check(bool color, Pos &check_1, Pos &check_2) const {
    check_2 = {-1, -1};
    Pos p = get_king_pos(color);
    if (!on_board(p)) return false;

    int check = 0;

    check += check_for_piece(p, {pieces[!color][0], pieces[!color][1]}, rook_moves, check_1);   //White is true==1 but white index is [0]

    check += check_for_piece(p, {pieces[!color][0], pieces[!color][2]}, bishop_moves, check ? check_2 : check_1);
    if(check >= 2) return check;

    check += check_for_piece(p, {pieces[!color][3]}, knight_moves, check ? check_2 : check_1);
    if(check >= 2) return check;

    check += check_for_piece(p, {pieces[!color][4]}, king_moves, check ? check_2 : check_1);
    if(check >= 2) return check;

    check += check_for_piece(p, {pieces[!color][5]}, pawn_capture_moves[!color], check ? check_2 : check_1);

    return check;
}

bool Board::in_check(bool color) const {
    Pos check1(-1, -1);
    Pos check2(-1, -1);
    return in_check(color, check1, check2);
}