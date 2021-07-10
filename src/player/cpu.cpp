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
    MoveEval m = evaluate_depth(g, DEPTH);
    //std::cout << "Done evals\n---------------\n";
    return m.move;
}

MoveEval evaluate_depth(Game &g, int depth) {
    MoveEval best;
    best.eval = std::numeric_limits<double>::lowest();
    double new_eval;
    auto moves = g.get_all_moves();
    if (moves.size() > 0) best.move = moves.front();
    else if (!g.get_check()) best.eval = 0.0;
    for (Move &m : g.get_all_moves()) {
        g.make_move(m);
        if (depth == 1) {
            new_eval = evaluate(g) + dist(gen);
            /*if (is_queen(g.get_board()[m.to.first][m.to.second])) {
                g.print_game();
                std::cout << "Eval is " << -new_eval << "\n";
            }*/
            if (-new_eval > best.eval) {    //This is called after a move is tried so it's the other person's turn (-eval)
                best.eval = -new_eval;
                best.move = m;
            }
        } else {
            MoveEval next = evaluate_depth(g, depth-1);
            /*if (next.eval <= -.1 || .1 <= next.eval) {
                g.print_game();
                std::cout << "Eval is " << -next.eval << "\n";
            }*/
            if (-next.eval > best.eval) {
                best.eval = -next.eval;
                best.move = m;
            }
        }

        g.unmake_move();
    }
    //std::cout << "\n\nEval at depth " << depth << " = " << best.eval << "\n\n\n";
    return best;
}

void CPU::print_player_type() {
    std::cout << "CPU player\n";
}

double evaluate(const Game &game) {
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