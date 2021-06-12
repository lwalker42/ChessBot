#define CATCH_CONFIG_MAIN
#include "../inc/catch.hpp"

#include <iostream>
#include <string>
#include "../src/board_constants.hpp"
#include "../src/util.hpp"
#include "../src/board.hpp"
#include "../src/move.hpp"
#include "../src/piece.hpp"
#include "../src/game.hpp"

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


const board_t test_board = {{{__,BB,BQ,BK,BB,BN,BR,BN},
                             {BP,__,BP,BP,BP,BP,BP,BP},
                             {__,WR,WN,WB,WQ,WK,WB,WN},
                             {__,__,__,__,__,__,__,__},
                             {__,__,__,__,__,__,__,__},
                             {__,__,__,__,__,__,__,__},
                             {WP,WP,WP,WP,WP,WP,__,WP},
                             {__,__,__,__,__,__,__,__}
                           }};
const board_t verify_init_board = {{{BR,BN,BB,BQ,BK,BB,BN,BR},
                                    {BP,BP,BP,BP,BP,BP,BP,BP},
                                    {__,__,__,__,__,__,__,__},
                                    {__,__,__,__,__,__,__,__},
                                    {__,__,__,__,__,__,__,__},
                                    {__,__,__,__,__,__,__,__},
                                    {WP,WP,WP,WP,WP,WP,WP,WP},
                                    {WR,WN,WB,WQ,WK,WB,WN,WR}
                                  }};


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

TEST_CASE("Comparing piece colors") {
    CHECK(same_color(WK, WQ));
    CHECK(same_color(WK, WP));
    CHECK(same_color(BK, BQ));
    CHECK(same_color(BN, BP));
    CHECK(!same_color(WK, BQ));
    CHECK(!same_color(WK, BK));
    CHECK(!same_color(WK, __));
    CHECK(!same_color(__, WK));
    CHECK(!same_color(__, BK));
}

const board_t _sparse_board = {{{__,__,__,__,__,__,__,__},
                                {__,__,__,__,__,__,__,__},
                                {__,__,__,__,__,__,__,__},
                                {__,__,__,WQ,__,__,__,__},
                                {__,__,__,__,__,__,__,__},
                                {__,__,__,__,__,__,__,__},
                                {__,__,__,__,__,__,__,__},
                                {__,__,__,__,__,__,__,__},
                              }};
const Board sparse_board(_sparse_board);


TEST_CASE("Retrieving move lists") {
    Board board;
    const moves_t black_king = {};
    const moves_t white_pawn = {M(-1, 0), M(-2, 0)};
    const moves_t white_knight = {M(-2, 1), M(-2, -1)};
    moves_t moves = board.get_moves(0, 4);
    CHECK(move::to_string(moves) == move::to_string(black_king));
    moves = board.get_moves(6, 2, PAWN_STARTING);
    CHECK(move::to_string(moves) == move::to_string(white_pawn));
    moves = board.get_moves(7, 6);
    CHECK(move::to_string(moves) == move::to_string(white_knight));

    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == 3 && j == 3) continue;
            moves = sparse_board.get_moves(i, j);
            CHECK(move::to_string(moves) == "");

        }
    }
    const moves_t queen_moves = {M(1, 1), M(2, 2), M(3, 3), M(4, 4), 
                                 M(-1, -1), M(-2, -2), M(-3, -3), 
                                 M(1, -1), M(2, -2), M(3, -3), 
                                 M(-1, 1), M(-2, 2), M(-3, 3), 
                                 M(1, 0), M(2, 0), M(3, 0), M(4, 0), 
                                 M(-1, 0), M(-2, 0), M(-3, 0), 
                                 M(0, 1), M(0, 2), M(0, 3), M(0, 4), 
                                 M(0, -1), M(0, -2), M(0, -3)};
    moves = sparse_board.get_moves(3, 3);
    CHECK(move::to_string(moves) == move::to_string(queen_moves));
}

TEST_CASE("Testing game object") {
    Game game;
}