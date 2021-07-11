#include <iostream>
#include <random>
#include <chrono>

#include "cpu.hpp"

#define DEPTH 4

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine gen(seed);
std::normal_distribution<double> dist(0.0, P_VAL/10);


Move CPU::get_move(const Game &game) {
    //std::cout << "Starting evals\n---------------\n";
    Game g(game);
    g.display = false;
    int depth = DEPTH;
    if (is_endgame(g)) depth += 2;
    MoveEval m = evaluate_depth(g, depth, MIN-depth*P_VAL, MAX+depth*P_VAL);
    //std::cout << "Done evals\n---------------\n";
    return m.move;
}

MoveEval evaluate_depth(Game &g, int depth, double alpha, double beta) {
    //std::cout << "(" << alpha << ", " << beta << ")\n";
    MoveEval best;
    best.eval = MIN-depth*P_VAL;
    double new_eval;
    auto moves = g.get_all_moves();
    if (moves.size() > 0) best.move = moves.front();
    else if (!g.get_check()) best.eval = 0.0;       //If no legal moves and not in check, then stalemate
    for (Move &m : g.get_all_moves()) {
        g.make_move(m);

        if (depth == 1) {
            new_eval = -(evaluate_board(g) + dist(gen));  //Evaluated from other player's pov so (-eval)
        } else {
            int new_depth = depth;
            if (!g.get_check()) new_depth--;
            new_eval = -evaluate_depth(g, new_depth, -beta, -alpha).eval;
        }

        if (new_eval > best.eval) {
            best.eval = new_eval;
            best.move = m;
        }
        if (best.eval >= beta) {
            g.unmake_move();
            break;
        }
        alpha = std::max(alpha, best.eval);

        g.unmake_move();
    }
    //std::cout << "\n\nEval at depth " << depth << " = " << best.eval << "\n\n\n";
    return best;
}

void CPU::print_player_type() {
    std::cout << "CPU player\n";
}

double evaluate_board(const Game &game) {
    board_t board = game.get_board();
    double total = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            total += evaluate_piece(board[i][j], i, j);
        }
    }
    return total * (game.get_turn() ? 1 : -1); 
}

double evaluate_piece(piece_t p, int i, int j) {
    double eval, weight;
    if (get_color(p)) {
        eval = 1.0;
        weight = WEIGHT * board_weights[get_piece(p)][i][j];
    } else {
        eval = -1.0;
        weight = -1 * WEIGHT * board_weights[get_piece(p)][BOARD_SIZE-1-i][BOARD_SIZE-1-j];
    }
    switch (get_piece(p)) {
        case KING:
            eval *= K_VAL;
            break;
        case QUEEN:
            eval *= Q_VAL;
            break;
        case ROOK:
            eval *= R_VAL;
            break;
        case BISHOP:
            eval *= B_VAL;
            break;
        case KNIGHT:
            eval *= N_VAL;
            break;
        case PAWN:
            eval *= P_VAL;
            break;
        default:
            return 0;
    }
    return eval + weight;
}

bool is_endgame(const Game &game) {
    board_t board = game.get_board();
    int blanks = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (is_empty(board[i][j])) blanks++;
        }
    }
    return blanks > (64 - 8);

}