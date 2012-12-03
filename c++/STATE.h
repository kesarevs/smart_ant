#ifndef STATE_H
#define STATE_H

enum ACTION {
    MOVE = 0,
    TURN_RIGHT = 1,
    TURN_LEFT = 2,
    NOTHING = 3
};

class STATE {
public:
    int outState0;
    int outState1;
    ACTION actionToMove0;
    ACTION actionToMove1;

    STATE(int out0 = 0, int out1 = 0, ACTION action0 = NOTHING, ACTION action1 = NOTHING);
    ~STATE();
    int getOutState(int id);
    ACTION getAction(int id);
};

#endif