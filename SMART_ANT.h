#ifndef SMART_ANT_H
#define SMART_ANT_H

#include "ANT.h"
#include <vector>

class SMART_ANT {
private:
    static const int bigShake = 60;
    static const int littleShake = 20;
    static const int generationSize = 50000;
    static const int survivedAnts = 1000;

    std::vector<ANT *> generation;
    int maxStepToAnt;
    int sizeOfMap; 
    int appleNumber;
    char ** torMap;
    int genomeSize;
    int generationNumber;

public:

    SMART_ANT(const int genomSize, const int maxStep, const int mapSize, const int apples, char ** map);
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