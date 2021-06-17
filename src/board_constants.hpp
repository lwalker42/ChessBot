#ifndef BOARD_CONSTANTS_HPP
#define BOARD_CONSTANTS_HPP

#include <functional>

#include "piece.hpp"
#include "move.hpp"
#include "type_defs.hpp"


const board_t init_board = {{{BR,BN,BB,BQ,BK,BB,BN,BR},
                             {BP,BP,BP,BP,BP,BP,BP,BP},
                             {__,__,__,__,__,__,__,__},
                             {__,__,__,__,__,__,__,__},
                             {__,__,__,__,__,__,__,__},
                             {__,__,__,__,__,__,__,__},
                             {WP,WP,WP,WP,WP,WP,WP,WP},
                             {WR,WN,WB,WQ,WK,WB,WN,WR}
                            }};

const diffs2_t bishop_moves = {{P(1, 1), P(2, 2), P(3, 3), P(4, 4),
                                P(5, 5), P(6, 6), P(7, 7)},
                               {P(-1, -1), P(-2, -2), P(-3, -3), P(-4, -4),
                                P(-5, -5), P(-6, -6), P(-7, -7)},
                               {P(1, -1), P(2, -2), P(3, -3), P(4, -4),
                                P(5, -5), P(6, -6), P(7, -7)},
                               {P(-1, 1), P(-2, 2), P(-3, 3), P(-4, 4),
                                P(-5, 5), P(-6, 6), P(-7, 7)}
                              };

const diffs2_t rook_moves = {{P(1, 0), P(2, 0), P(3, 0), P(4, 0), 
                              P(5, 0), P(6, 0), P(7, 0)},
                             {P(-1, 0), P(-2, 0), P(-3, 0), P(-4, 0), 
                              P(-5, 0), P(-6, 0), P(-7, 0)},
                             {P(0, 1), P(0, 2), P(0, 3), P(0, 4),
                              P(0, 5), P(0, 6), P(0, 7)},
                             {P(0, -1), P(0, -2), P(0, -3), P(0, -4),
                              P(0, -5), P(0, -6), P(0, -7)}
                            };

const diffs2_t queen_moves = {{P(1, 1), P(2, 2), P(3, 3), P(4, 4),
                               P(5, 5), P(6, 6), P(7, 7)},
                              {P(-1, -1), P(-2, -2), P(-3, -3), P(-4, -4),
                               P(-5, -5), P(-6, -6), P(-7, -7)},
                              {P(1, -1), P(2, -2), P(3, -3), P(4, -4),
                               P(5, -5), P(6, -6), P(7, -7)},
                              {P(-1, 1), P(-2, 2), P(-3, 3), P(-4, 4),
                               P(-5, 5), P(-6, 6), P(-7, 7)},
                              {P(1, 0), P(2, 0), P(3, 0), P(4, 0), 
                               P(5, 0), P(6, 0), P(7, 0)},
                              {P(-1, 0), P(-2, 0), P(-3, 0), P(-4, 0), 
                               P(-5, 0), P(-6, 0), P(-7, 0)},
                              {P(0, 1), P(0, 2), P(0, 3), P(0, 4),
                               P(0, 5), P(0, 6), P(0, 7)},
                              {P(0, -1), P(0, -2), P(0, -3), P(0, -4),
                               P(0, -5), P(0, -6), P(0, -7)}
                             };

const diffs2_t knight_moves = {{P(-2, 1)}, {P(-2, -1)}, {P(-1, -2)}, {P(1, -2)}, 
                               {P(2, -1)}, {P(2, 1)}, {P(1, 2)}, {P(-1, 2)}
                              };

const diffs2_t king_moves = {{P(1, 0)}, {P(1, 1)}, {P(0, 1)}, {P(-1, 1)}, 
                             {P(-1, 0)}, {P(-1, -1)}, {P(0, -1)}, {P(1, -1)}
                            };
const diffs2_t kingside_moves = {{P(0, 1), P(0, 2)}};
const diffs2_t queenside_moves = {{P(0, -1), P(0, -3), P(0, -2)}};

//WHITE is first set, BLACK is second set
const diffs2_t pawn_first_moves[] = {{{P(-1, 0), P(-2, 0)}},  {{P(1, 0), P(2, 0)}}};
const diffs2_t pawn_moves[] = {{{P(-1, 0)}},  {{P(1, 0)}}};
const diffs2_t pawn_capture_moves[] = {{{P(-1, -1)}, {P(-1, 1)}},  {{P(1, 1)}, {P(1, -1)}}};
const pieces_t promotions[] = {{WQ, WR, WB, WN},
                               {BQ, BR, BB, BN}};

const moves_t kingside[] = {{Move(P(7, 4), P(7, 5)), Move(P(7, 4), P(7, 6), KINGSIDE)}, {Move(P(0, 4), P(0, 5)), Move(P(0, 4), P(0, 6), KINGSIDE)}};
const moves_t queenside[] = {{Move(P(7, 4), P(7, 3)), Move(P(7, 4), P(7, 2), QUEENSIDE)}, {Move(P(0, 4), P(0, 3)), Move(P(0, 4), P(0, 2), QUEENSIDE)}};

#endif