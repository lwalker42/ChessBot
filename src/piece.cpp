//#include <iostream>
//#include <string>
#include "piece.h"

using namespace std; 


char toString(P iece p) {
    switch(p) {
        case king:
        return 'K';
        case queen:
        return 'Q';
        case rook:
        return 'R';
        case bishop:
        return 'B';
        case knight:
        return 'N';
        case pawn:
        return 'P';
        default:
        return '-';
    }
}