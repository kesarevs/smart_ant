#ifndef GENOME_H
#define GENOME_H

#include "STATE.h"


class GENOME {
private:
	int genomSize;
	int startState;
	STATE ** states;

public:

    GENOME(const int size);
    ~GENOME();

    STATE * getState(const int id) const;
    int getStartState() const;
    int getGenomeSize() const;

    void changeStartState(const int st);
    void changeState(const int id, STATE * st);
};

#endif