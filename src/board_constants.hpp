#ifndef BOARD_CONSTANTS_HPP
#define BOARD_CONSTANTS_HPP

#include <array>
#include "piece.hpp"
#include "move.hpp"

#define BOARD_SIZE 8

typedef std::array<std::array<piece_t, BOARD_SIZE>, BOARD_SIZE> board_t;

const board_t init_board = {{{BR,BN,BB,BQ,BK,BB,BN,BR},
                             {BP,BP,BP,BP,BP,BP,BP,BP},
                             {__,__,__,__,__,__,__,__},
                             {__,__,__,__,__,__,__,__},
                             {__,__,__,__,__,__,__,__},
                             {__,__,__,__,__,__,__,__},
                             {WP,WP,WP,WP,WP,WP,WP,WP},
                             {WR,WN,WB,WQ,WK,WB,WN,WR}
                            }};

const moves2_t bishop_moves = {{M(1, 1), M(2, 2), M(3, 3), M(4, 4),
                                M(5, 5), M(6, 6), M(7, 7)},
                               {M(-1, -1), M(-2, -2), M(-3, -3), M(-4, -4),
                                M(-5, -5), M(-6, -6), M(-7, -7)},
                               {M(1, -1), M(2, -2), M(3, -3), M(4, -4),
                                M(5, -5), M(6, -6), M(7, -7)},
                               {M(-1, 1), M(-2, 2), M(-3, 3), M(-4, 4),
                                M(-5, 5), M(-6, 6), M(-7, 7)}
                              };

const moves2_t rook_moves = {{M(1, 0), M(2, 0), M(3, 0), M(4, 0), 
                              M(5, 0), M(6, 0), M(7, 0)},
                             {M(-1, 0), M(-2, 0), M(-3, 0), M(-4, 0), 
                              M(-5, 0), M(-6, 0), M(-7, 0)},
                             {M(0, 1), M(0, 2), M(0, 3), M(0, 4),
                              M(0, 5), M(0, 6), M(0, 7)},
                             {M(0, -1), M(0, -2), M(0, -3), M(0, -4),
                              M(0, -5), M(0, -6), M(0, -7)}
                            };

const moves2_t queen_moves = {{M(1, 1), M(2, 2), M(3, 3), M(4, 4),
                               M(5, 5), M(6, 6), M(7, 7)},
                              {M(-1, -1), M(-2, -2), M(-3, -3), M(-4, -4),
                               M(-5, -5), M(-6, -6), M(-7, -7)},
                              {M(1, -1), M(2, -2), M(3, -3), M(4, -4),
                               M(5, -5), M(6, -6), M(7, -7)},
                              {M(-1, 1), M(-2, 2), M(-3, 3), M(-4, 4),
                               M(-5, 5), M(-6, 6), M(-7, 7)},
                              {M(1, 0), M(2, 0), M(3, 0), M(4, 0), 
                               M(5, 0), M(6, 0), M(7, 0)},
                              {M(-1, 0), M(-2, 0), M(-3, 0), M(-4, 0), 
                               M(-5, 0), M(-6, 0), M(-7, 0)},
                              {M(0, 1), M(0, 2), M(0, 3), M(0, 4),
                               M(0, 5), M(0, 6), M(0, 7)},
                              {M(0, -1), M(0, -2), M(0, -3), M(0, -4),
                               M(0, -5), M(0, -6), M(0, -7)}
                             };

const moves2_t king_moves = {{M(1, 0)}, {M(1, 1)}, {M(0, 1)}, {M(-1, 1)}, 
                             {M(-1, 0)}, {M(-1, -1)}, {M(0, -1)}, {M(1, -1)}
                            };

const moves2_t knight_moves = {{M(1, 2)}, {M(1, -2)}, {M(-1, 2)}, {M(-1, 2)}, 
                               {M(2, 1)}, {M(2, -1)}, {M(-2, 1)}, {M(-2, -1)}
                              };

const moves2_t pawn_first_moves = {{M(0, -1), M(0, -2)}};
const moves2_t pawn_moves = {{M(0, -1)}};
const moves2_t pawn_capture_moves = {{M(1, -1)}, {M(-1, -1)}};

#endif