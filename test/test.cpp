#define CATCH_CONFIG_MAIN
#include "../inc/catch.hpp"

#include <iostream>
#include <string>
#include "../src/board_constants.hpp"
#include "../src/util.hpp"
#include "../src/board.hpp"
#include "../src/move.hpp"

TEST_CASE("Test board bounds") {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++){
            CHECK(on_board(i, j));
        }
    }
    CHECK(!on_board(-1, 0));
    CHECK(!on_board(0, -1));
    CHECK(!on_board(-1, -1));
    CHECK(!on_board(BOARD_SIZE, 0));
    CHECK(!on_board(0, BOARD_SIZE));
    CHECK(!on_board(BOARD_SIZE, BOARD_SIZE));
}

const board_t test_board = {{{_, b, q, k, b, n, r, n},
                             {p, _, p, p, p, p, p, p},
                             {_, R, N, B, Q, K, B, N},
                             {_, _, _, _, _, _, _, _},
                             {_, _, _, _, _, _, _, _},
                             {_, _, _, _, _, _, _, _},
                             {P, P, P, P, P, P, _, P},
                             {_, _, _, _, _, _, _, _}}};
const board_t verify_init_board = {{{r, n, b, q, k, b, n, r},
                                    {p, p, p, p, p, p, p, p},
                                    {_, _, _, _, _, _, _, _},
                                    {_, _, _, _, _, _, _, _},
                                    {_, _, _, _, _, _, _, _},
                                    {_, _, _, _, _, _, _, _},
                                    {P, P, P, P, P, P, P, P},
                                    {R, N, B, Q, K, B, N, R}}};

TEST_CASE("Moving pieces (arbitrarily) on the board") {
    Board board;
    CHECK(board.get_board() == init_board);

    for (int i = 0; i < BOARD_SIZE; i++) {
        board.move_piece(i, i);
        board.move_piece(0, (i+1)%BOARD_SIZE, 0, i);
        board.move_piece(BOARD_SIZE-1, BOARD_SIZE-1-i, 2, BOARD_SIZE-i);
    }
    CHECK(board.get_board() == test_board);
    CHECK(board.get_board() != init_board); //Make sure a deep copy is made during initialization
    CHECK(init_board == verify_init_board);
}

TEST_CASE("Retrieving move lists") {
    Board board;
    const moves_t black_king = {};
    const moves_t white_pawn = {M(0, -1), M(0, -2)};
    const moves_t white_knight = {M(-1, -2), M(1, -2)};
    moves_t moves = board.get_moves(0, 4);
    CHECK(to_string(moves) == to_string(black_king));
    moves = board.get_moves(6, 2);
    CHECK(to_string(moves) == to_string(white_pawn));
    moves = board.get_moves(7, 6);
    CHECK(to_string(moves) == to_string(white_knight));
}