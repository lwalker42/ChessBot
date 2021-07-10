#include <iostream>
#include <string>
#include <algorithm>

#include "util.hpp"
#include "piece.hpp"
#include "game.hpp"
#include "piece_util.hpp"
#include "player/player.hpp"
#include "move.hpp"
#include "board_constants.hpp"
#include "timer.hpp"

Game::Game(int w_type, int b_type, board_t b, bool t, bool wk, bool wq, bool bq, bool bk) {
    init_player_types();
    PGN = "";
    white = w_type;
    black = b_type;
    ply_count = 0;
    board = Board (b);
    turn = t;
    check = board.in_check(turn, check_1, check_2);
    finished = false;
    en_passant = false;
    white_kingside = wk;
    white_queenside = wq;
    black_kingside = bk;
    black_queenside = bq;
    display = true;
}

board_t Game::get_board() const {
    return board.get_board();
}

bool Game::get_turn() const {
    return turn;
}

bool Game::get_check() const {
    return check;
}

void Game::print_game() {
    std::cout << std::endl << board.to_string();
    std::cout << (turn ? "White's turn\n" : "Black's turn\n");
    std::cout << (check ? "You are in check!\n" : "");
}

void Game::play_game() {
    while(!finished) {
        if(display) print_game();
        Player *p = player_types[turn ? white : black];
        Move m = p->get_move(*this);
        if (m.from.first == 'U' && game_moves.size() > 0) {
            unmake_move();
            std::cout << "Undoing moves...\n";
            continue;
        }
        if (!valid_move(m)) {
            std::cout << "\n\nInvalid move\n";
            continue;
        }
        make_move(m);
        if (check) in_checkmate();
    }
    std::cout << "\n" << board.to_string();
    std::cout << "Game over.  " << (turn ? "Black" : "White") << " wins!\n";
    print_PGN();
}

void Game::make_move(Move &m) {
    if (display) std::cout << add_to_PGN(m) << "\n";
    handle_special(m);
    board.move_piece(m);
    game_moves.push_back(m);
    check = board.in_check(!turn, check_1, check_2);
    ply_count++;
    turn = !turn;
    if (display && check) PGN += "+";
}

void Game::unmake_move() {
    Move m = game_moves.back();
    game_moves.pop_back();

    unhandle_special(m);
    board.unmove_piece(m);
    turn = !turn;
    ply_count--;
    finished = false;
}

moves_t Game::get_all_moves() {
    moves_t moves;
    board_t b = board.get_board();
    Pos king_pos = board.get_king_pos(turn);
    pos_t blocking = get_blocking(king_pos);
    blocking.push_back(king_pos);
    piece_t p = __;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            p = b[i][j];
            if (is_empty(p)) continue;
            if (get_color(p) == turn) {
                if (check) {
                    if (on_board(check_2) && !is_king(p)) continue;
                    //TODO Check cases
                    /*if (!on_board(check_2)) {   //Only one piece is delivering check
                        moves_t captures = get_moves(i, j, p, true, true);
                        moves.insert(moves.end(), captures.begin(), captures.end());
                        if (b[check_1])
                    }*/
                    moves_t p_moves = get_moves(i, j, p);
                    moves.insert(moves.end(), p_moves.begin(), p_moves.end());
                    
                } else {                        //Not in check
                    Pos pos = {i, j};
                    if (std::find(blocking.begin(), blocking.end(), pos) != blocking.end()) {
                        moves_t p_moves = get_moves(i, j, p);
                        moves.insert(moves.end(), p_moves.begin(), p_moves.end());
                    } else {
                        moves_t p_moves = get_moves(i, j, p, false, false);
                        moves.insert(moves.end(), p_moves.begin(), p_moves.end());
                    }
                }
            }
        }
    }
    /*auto it = std::find_if(moves.begin(), moves.end(), [this](Move m){return m.sm == KINGSIDE || m.sm == QUEENSIDE;});
    if (it != moves.end()) {
        std::cout << board.to_string();
        std::cout << "Failed with move: " << (*it).to_string() << "\n";
    }*/
    return moves;
}


bool Game::valid_move(Move &m) {
    if (!on_board(m.from)) return NULL;      //Initial piece is on board
    if (!on_board(m.to)) return NULL;  //Target location is on board

    piece_t piece = board[m.from];
    if (is_empty(piece)) return NULL;           //Check that piece is non-empty
    if (get_color(piece) != turn) return NULL;  //Check that piece is the current player's piece

    moves_t moves = get_all_moves();
    //for (auto move : moves) std::cout << move.to_string() << "\n";
    auto it = std::find_if(moves.begin(), moves.end(), 
                           [&m](Move move) -> bool {return m.from == move.from
                                                        && m.to == move.to
                                                        && (m.promotion == __ || m.promotion == abs(move.promotion));});  //Check if move is a valid move
    if (it == moves.end()) {
        return false;
    } else {
        m = *it;
        return true;
    }
}


moves_t Game::get_moves(int r, int c, piece_t piece, bool capture_only, bool filter) {
    moves_t moves;

    if (is_pawn(piece)) {                                           //If pawn
        if (!capture_only) {
            if (is_pawn_first(r, c, piece)) {                           //First get non-capturing moves
                moves = board.get_moves(r, c, PAWN_STARTING);           //Move 1 or 2
            } else {
                moves = board.get_moves(r, c, MOVE_ONLY);               //Move 1
            }
        }
        moves_t moves2 ( en_passant 
                           ? board.get_moves(r, c, CAPTURE_ONLY, en_passant_pos)  
                           : board.get_moves(r, c, CAPTURE_ONLY));   //Then get capturing moves
        moves.insert(moves.end(), moves2.begin(), moves2.end());
                                                                    //TODO Then handle promotion
    } else if(is_king(piece)) {
        moves = board.get_moves(r, c, capture_only ? CAPTURE_ONLY : NONE);
        bool col = get_color(piece);
        if(!capture_only) {
            moves_t kings = board.get_moves(r, c, KINGSIDE);
            moves_t queens = board.get_moves(r, c, QUEENSIDE);
            if (kings.size() > 0 && try_castle(col, KINGSIDE)) moves.push_back(kings[0]);
            if (queens.size() > 0 && try_castle(col, QUEENSIDE)) moves.push_back(queens[0]);
        }
    } else {
        moves = board.get_moves(r, c, capture_only ? CAPTURE_ONLY : NONE);
    }
    return (filter || (en_passant && is_pawn(piece)) ? filter_check(moves) : moves);
}

moves_t Game::get_moves(Pos p, piece_t piece, bool capture_only, bool filter) {
    return get_moves(p.first, p.second, piece, capture_only, filter);
}

pos_t Game:: get_blocking(Pos king) {
    pos_t blocking;
    for (diffs_t m_list : king_moves) {
        Pos m = m_list.front();
        Pos pos = king;
        Pos block = {-1 , -1};
        while (true) {
            pos.first += m.first;
            pos.second += m.second;
            if (!on_board(pos)) break;
            piece_t p = board[pos];
            if (is_empty(p))  continue;

            if (get_color(p) == turn && !on_board(block)) {
                block = pos;
                continue;
            } else if (get_color(p) != turn && on_board(block)) {
                if (is_pawn(p) || is_knight(p) || is_king(p)) break;
                else if ((m.first && m.second) && (is_bishop(p) || is_queen(p)))
                    blocking.push_back(block);
                else if ((m.first ^ m.second) && (is_rook(p) || is_queen(p)))
                    blocking.push_back(block);
            }
            block = {-1, -1};
            break;

        }
    }
    return blocking;
}


//filter_check helper: remove if move puts current player in check
bool Game::try_move_check(const Move &move) {
    board.move_piece(move);
    bool in_check = board.in_check(turn);
    board.unmove_piece(move);
    return in_check;
}

moves_t Game::filter_check(moves_t moves) {
    //std::cout << "Before filter: " << move::to_string(moves) << "\n";
    moves.erase(std::remove_if(moves.begin(), 
                               moves.end(), 
                               [this](Move m){return this->try_move_check(m);}), moves.end());
    
    //std::cout << "After filter: " << move::to_string(moves) << "\n";
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
    if (finished) return true;
    if (!check) return false;
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
    PGN.back() = '#';
    return true;
}


void Game::handle_special(Move &move) {
    piece_t p = board[move.from];
    bool c = get_color(p);
    move.game_flags = check 
                    | (white_kingside << 1)
                    | (white_queenside << 2)
                    | (black_kingside << 3)
                    | (black_queenside << 4)
                    | (en_passant << 5);
    if (move.sm == PAWN_STARTING) {
        en_passant = true;
        en_passant_pos = move.to;
        return;
    } else if (c ? (white_kingside || white_queenside)
                 : (black_kingside || black_queenside)) {
        if (is_king(p)) {                                       //Check if king moves
            (c ? white_kingside : black_kingside) = false;
            (c ? white_queenside : black_queenside) = false;
        } else if ((c ? white_kingside : black_kingside)        //Check is kingside rook moves
                 && is_kingside(move.from, p)) {
            (c ? white_kingside : black_kingside) = false;
        } else if ((c ? white_queenside : black_queenside)      //Check is queenside rook moves
                 && is_queenside(move.from, p)) {
            (c ? white_queenside : black_queenside) = false;
        }
    }
    if (c ? (black_kingside || black_queenside)
          : (white_kingside || white_queenside)) {
        if ((c ? black_kingside : white_kingside)               //Check is kingside rook is captured
                 && is_kingside(move.to, board[move.to])) {
            (c ? black_kingside : white_kingside) = false;
        } else if ((c ? black_queenside : white_queenside)      //Check is queenside rook is captured
                 && is_queenside(move.to, board[move.to])) {
            (c ? black_queenside : white_queenside) = false;
        }
    }
    en_passant = false;
}

void Game::unhandle_special(Move &move) {
    int f = move.game_flags;
    check = f & 1;
    white_kingside = f & (1 << 1);
    white_queenside = f & (1 << 2);
    black_kingside = f & (1 << 3);
    black_queenside = f & (1 << 4);
    en_passant = f & (1 << 5);
    if (move.sm == EN_PASSANT) {
        en_passant_pos = game_moves.back().to;
    }
}


int Game::perft(int depth) {
    if (depth <= 0) return 1;
    if (depth <= 1) return get_all_moves().size();
    //std::cout << board.to_string();

    int num_moves = 0;
    for (Move move : get_all_moves()) {
        make_move(move);
        num_moves += perft(depth-1);
        unmake_move();
    }
    if (depth >= 5) {
        std::cout << num_moves << " moves at depth " << depth << "\n";
        std::cout << board.to_string(); 
        std::cout << "\n\n";
    }
    return num_moves;
}

char to_file(int c) {
    return (char) (c + 'a');
}

char to_rank(int r) {
    return (char) ('8' - r);
}

std::string Game::add_to_PGN(Move &m) {
    std::string str;

    if (m.sm == KINGSIDE) str = "O-O";
    else if (m.sm == QUEENSIDE) str = "O-O-O";
    else {
        piece_t p = board[m.from];
        piece_t cap = m.captured;

        moves_t all = get_all_moves();
        all.erase(std::remove_if(all.begin(), all.end(), [m, p, this](Move &move) {return (p != board[move.from]) || (m.to != move.to) || (m.from == move.from);}), all.end());
        
        if (!is_pawn(p)) {
            str += toupper(to_char(p));
            if(all.size() > 0) {
                if (std::none_of(all.begin(), all.end(), [m](Move &move) {return m.to.second == move.to.second;})) {
                    str += to_file(m.from.second);
                } else if (std::none_of(all.begin(), all.end(), [m](Move &move) {return m.to.first == move.to.first;})) {
                    str += to_rank(m.from.first);
                } else {
                    str += to_file(m.from.second);
                    str += to_rank(m.from.first);
                }
            }
        } else if (!is_empty(cap)) {
            str += to_file(m.from.second);
        }
        if (!is_empty(cap)) str += "x";
        str += to_file(m.to.second);
        str += to_rank(m.to.first);
        if (m.sm == PROMOTION) str += "=" + toupper(to_char(m.promotion));
    }

    if (turn) {
        PGN += "\n" + std::to_string(ply_count/2 + 1) + ".";
    }
    PGN += " " + str;

    return str;
}
        
void Game::print_PGN() const {
    std::cout << "\nPGN: \n" << PGN << "\n";
}