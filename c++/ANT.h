#ifndef ANT_H
#define ANT_H

#include "GENOME.h"

class ANT {
private:
    float prior;
    int applesWasEat;
    int moveToEatAllApples;
    GENOME * genome;

public:

	ANT(const int size, GENOME* g = 0);
	~ANT();

    float returnPriority() const;
    int returnAppleNumber() const;
    GENOME * getGenome() const;

    void changePrior(const float p);
	void makeMoves(const int maxStep, const int mapSize, const int appleNumber, char ** map);
};

#endif