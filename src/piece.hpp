#ifndef PIECE_HPP
#define PIECE_HPP


#define WHITE true
#define BLACK false

//White > 0; Black < 0; empty == 0
enum piece_t {
    __=0,
    WK='K', WQ='Q', WR='R', WB='B', WN='N', WP='P',
    BK=-'K', BQ=-'Q', BR=-'R', BB=-'B', BN=-'N', BP=-'P' 
};

char to_char(piece_t);

inline bool is_empty(piece_t p) {
    return p == __;
}

inline bool get_color(piece_t p) {
    return p > 0;
}

inline bool same_color(piece_t p1, piece_t p2) {
    return (p1 != __) && (p2 != __) && ((p1 > 0) == (p2 > 0));  //Check if either are empty
}

inline bool is_pawn(piece_t p) {
    return abs(p) == WP;
}

inline bool is_king(piece_t p) {
    return abs(p) == WK;
}

inline bool is_rook(piece_t p) {
    return abs(p) == WR;
}

inline bool is_bishop(piece_t p) {
    return abs(p) == WB;
}

inline bool is_knight(piece_t p) {
    return abs(p) == WN;
}

inline bool is_queen(piece_t p) {
    return abs(p) == WQ;
}


#endif