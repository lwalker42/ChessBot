#ifndef MOVE_H
#define MOVE_H

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