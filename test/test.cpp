#define CATCH_CONFIG_MAIN
#include "../inc/catch.hpp"
#include "../src/board_constants.hpp"
#include "../src/util.hpp"
#include "../src/board.hpp"

TEST_CASE("Test board bounds") {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++){
            REQUIRE(on_board(i, j));
        }
    }
    REQUIRE(!on_board(-1, 0));
    REQUIRE(!on_board(0, -1));
    REQUIRE(!on_board(-1, -1));
    REQUIRE(!on_board(BOARD_SIZE, 0));
    REQUIRE(!on_board(0, BOARD_SIZE));
    REQUIRE(!on_board(BOARD_SIZE, BOARD_SIZE));
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
    REQUIRE(board.get_board() == init_board);

    for (int i = 0; i < BOARD_SIZE; i++) {
        board.move_piece(i, i);
        board.move_piece(0, (i+1)%BOARD_SIZE, 0, i);
        board.move_piece(BOARD_SIZE-1, BOARD_SIZE-1-i, 2, BOARD_SIZE-i);
    }
    REQUIRE(board.get_board() == test_board);
    REQUIRE(board.get_board() != init_board); //Make sure a deep copy is made during initialization
    REQUIRE(init_board == verify_init_board);
}