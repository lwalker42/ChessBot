#include <iostream>
#include <random>
#include <chrono>

#include "cpu.hpp"

Move CPU::get_move(const Game &game) {
    Game g(game);
    Move best;
    double eval = std::numeric_limits<double>::lowest();
    double new_eval;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::normal_distribution<double> dist(0.0, 0.1);
    
    //std::cout << "Starting evals\n---------------\n";
    for (Move &m : g.get_all_moves()) {
        g.make_move(m);
        new_eval = evaluate(g) + dist(gen);
        //g.print_game();
        //std::cout << "Eval is " << new_eval << "\n";
        if (new_eval > eval) {
            eval = new_eval;
            best = m;
        }
        g.unmake_move();
    }
    //std::cout << "Done evals\n---------------\n";
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
            total += evaluate_piece(board[i][j]);
        }
    }
    return total * (!game.get_turn() ? 1 : -1);
}

double evaluate_piece(piece_t p) {
    double color = get_color(p) ? 1.0 : -1.0;
    if (is_pawn(p)) return P_VAL * color;
    if (is_knight(p)) return N_VAL * color;
    if (is_bishop(p)) return B_VAL * color;
    if (is_rook(p)) return R_VAL * color;
    if (is_queen(p)) return Q_VAL * color;
    if (is_king(p)) return K_VAL * color;
    return 0;
}