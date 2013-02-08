#include "GENOME.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>

GENOME::GENOME(const int size) : genomSize(size) {
    states = new STATE * [genomSize];
    startState = rand() % genomSize;
    for (int i = 0; i < genomSize; i++) {
        states[i] = new STATE(rand() % genomSize, rand() % genomSize, 
                            (ACTION) (rand() % 4), (ACTION) (rand() % 4));
    }
}

GENOME::~GENOME() {
    for (int i = 0; i < genomSize; i++) {
        delete states[i];
    }
    delete states;
}

void GENOME::changeState(const int id, STATE * st) {
    assert(id >= 0 && id < genomSize);
    delete states[id];
    states[id] = st;
}

STATE * GENOME::getState(const int id) const {
    assert(id >= 0 && id < genomSize);
    return states[id];
}

int GENOME::getStartState() const {
    return startState;
}

void GENOME::changeStartState(const int st) {
    startState = st;
}

int GENOME::getGenomeSize() const {
    return genomSize;
}