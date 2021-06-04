#ifndef MOVE_HPP
#define MOVE_HPP

struct Move;
typedef Move M;

struct Move {
    int r, c;
    
    Move () {
        r = 0;
        c = 0;
    }

    Move (int i, int j) {
        r = i;
        c = j;
    }

    int toString() const{
        return r*10 + c;
    }
};

#endif