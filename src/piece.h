#ifndef PIECE_H
#define PIECE_H

using namespace std;

enum Piece {
    empty,
    king,
    queen,
    rook,
    bishop,
    knight,
    pawn
};

char toString(Piece);

#endif