#ifndef PIECE_H
#define PIECE_H

using namespace std;

enum Piece {
    _,
    K, Q, R, B, N, P, 
    k, q, r, b, n, p
};

char to_char(Piece);
//string to_string(Piece);

#endif