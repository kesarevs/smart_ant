#ifndef SMART_ANT_H
#define SMART_ANT_H

#include "ANT.h"
#include <fstream>

class SMART_ANT {
private:
    int generationSize;
    int genomeSize;
    std::vector<ANT *> generation;
    std::vector<ANT *> antsToLove;
    int maxStepToAnt;
    int sizeOfMap; 
    int appleNumber;
    int ** torMap;
    int survivedAnts;
    int generationNumber;

public:
    SMART_ANT(int generSize, int survived, int genomSize, int maxStep, int mapSize, int apples, int ** map);
    ~SMART_ANT();
    ANT* makeMachine();
    void makeLittleShake();
    void makeBigShake();
    void makeMutation(ANT* ant);
    void makeLove(ANT* parent1, ANT* parent2);
    void makeFirstGeneration();
    void makeNextGeneration();
    void checkGeneration();
};

#endif