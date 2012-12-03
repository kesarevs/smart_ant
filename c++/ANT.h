#ifndef ANT_H
#define ANT_H

#include "GENOME.h"

class ANT {
private:
    float prior;
    int applesWasEat;
    int moveToEatAllApples;
    int rotation;
    int x;
    int y;

public:
    GENOME * genome;

	ANT(int size, GENOME* g = NULL);
	~ANT();
    void changePrior(float p);
	void makeMoves(int maxStep, int mapSize, int appleNumber, int ** map);
    float returnPriority();
    int returnAppleNumber();
};

#endif