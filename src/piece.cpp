//#include <iostream>
//#include <string>
#include <cctype>

#include "piece.hpp"

using namespace std; 

//White > 0; Black < 0; empty == 0
char to_char(piece_t p) {
    if (p == __) return '-';
    else if (p > 0) return p;
    else return -p;
}