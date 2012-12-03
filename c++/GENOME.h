#ifndef GENOME_H
#define GENOME_H

#include "STATE.h"
#include <vector>
class GENOME {

public:
    int genomSize;
    int startState;
    std::vector<STATE *> states;

    GENOME(int size);
    ~GENOME();
    STATE * getState(int id);
    STATE * getStartState();
};

#endif