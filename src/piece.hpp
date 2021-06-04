#ifndef PIECE_HPP
#define PIECE_HPP

enum Piece {
    _,                //0
    K, Q, R, B, N, P, //1, 2, 3, 4, 5, 6
    k, q, r, b, n, p  //7, 8, 9, 10, 11, 12
};

char to_char(Piece);
//string to_string(Piece);

#endif