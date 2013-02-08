#ifndef STATE_H
#define STATE_H

enum ACTION {
    MOVE = 0,
    TURN_RIGHT = 1,
    TURN_LEFT = 2,
    NOTHING = 3
};

class STATE {
private:
    int outStates[2];
    ACTION actionToMove[2];

public:
    STATE(const int out0 = 0, const int out1 = 0, const ACTION action0 = NOTHING, 
                                                    const ACTION action1 = NOTHING);
    ~STATE();

    ACTION getAction(const int id) const;
    int getOutState(const int id) const;
    
    void changeOutState(const int id, const int out);
    void changeAction(const int id, const ACTION act);
};

#endif