//#include <iostream>
//#include <string>
#include "piece.h"

using namespace std; 


char to_char(Piece piece) {
    switch(piece) {
        case K:
        return 'K';
        case Q:
        return 'Q';
        case R:
        return 'R';
        case B:
        return 'B';
        case N:
        return 'N';
        case P:
        return 'P';
        case k:
        return 'k';
        case q:
        return 'q';
        case r:
        return 'r';
        case b:
        return 'b';
        case n:
        return 'n';
        case p:
        return 'p';
        default:
        return '-';
    }
}