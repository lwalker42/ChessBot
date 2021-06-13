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
bool is_empty(piece_t);
bool get_color(piece_t);
bool same_color(piece_t, piece_t);
bool is_pawn(piece_t);
bool is_king(piece_t);


#endif