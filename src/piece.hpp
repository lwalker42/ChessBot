#ifndef PIECE_HPP
#define PIECE_HPP


#define PIECE_MASK 7
#define COLOR_MASK 8

#define EMPTY 0
#define KING 1
#define QUEEN 2
#define ROOK 3
#define BISHOP 4
#define KNIGHT 5
#define PAWN 6

#define WHITE true
#define BLACK false


enum piece_t {
    __=0,
    BK=1, BQ=2, BR=3, BB=4, BN=5, BP=6,
    WK=9, WQ=10, WR=11, WB=12, WN=13, WP=14 
};

char to_char(piece_t);

inline bool is_empty(piece_t p) {
    return (p & PIECE_MASK) == __;
}

inline bool get_color(piece_t p) {
    return p & COLOR_MASK;
}

inline int get_piece(piece_t p) {
    return p & PIECE_MASK;
}

inline bool same_color(piece_t p1, piece_t p2) {
    return ((p1 & COLOR_MASK) == (p2 & COLOR_MASK)) && (p1 & PIECE_MASK) && (p2 & PIECE_MASK);  //Check if either are empty
}

inline bool is_pawn(piece_t p) {
    return (p & PIECE_MASK) == PAWN;
}

inline bool is_king(piece_t p) {
    return (p & PIECE_MASK) == KING;
}

inline bool is_rook(piece_t p) {
    return (p & PIECE_MASK) == ROOK;
}

inline bool is_bishop(piece_t p) {
    return (p & PIECE_MASK) == BISHOP;
}

inline bool is_knight(piece_t p) {
    return (p & PIECE_MASK) == KNIGHT;
}

inline bool is_queen(piece_t p) {
    return (p & PIECE_MASK) == QUEEN;
}


#endif