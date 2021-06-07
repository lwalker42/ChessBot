#ifndef PIECE_HPP
#define PIECE_HPP

//White > 0; Black < 0; empty == 0
enum piece_t {
    __=0,
    WK='K', WQ='Q', WR='R', WB='B', WN='N', WP='P',
    BK=-'K', BQ=-'Q', BR=-'R', BB=-'B', BN=-'N', BP=-'P' 
};

char to_char(piece_t piece);


#endif