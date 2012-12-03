#include "GENOME.h"
#include <time.h>
#include <stdlib.h>

GENOME::GENOME(int size) : genomSize(size) {
    startState = rand() % genomSize;
    for (int i = 0; i < genomSize; i++) {
        int out0 = rand() % genomSize;
        int out1 = rand() % genomSize;
        ACTION action0 = (ACTION) (rand() % 4);
        ACTION action1 = (ACTION) (rand() % 4);
        states.push_back(new STATE(out0, out1, action0, action1));
    }
}


GENOME::~GENOME(void) {
    for (int i = 0; i < genomSize; i++) {
        delete states[i];
    }
}

STATE * GENOME::getState(int id) {
    return states[id];
}

STATE * GENOME::getStartState() {
    return states[startState];
}