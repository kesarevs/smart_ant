#include "SMART_ANT.h"
#include "STATE.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

bool comparePriority(ANT* ant1, ANT* ant2) {
    return (ant1->returnPriority() > ant2->returnPriority()); 
}


SMART_ANT::SMART_ANT(int generSize, int survived, int genomSize, int maxStep, int mapSize, int apples, int ** map) {
    srand(time(NULL));
    generationSize = generSize;
    genomeSize = genomSize;
    maxStepToAnt = maxStep;
    sizeOfMap = mapSize;
    appleNumber = apples;
    torMap = map;
    survivedAnts = survived;
    generationNumber = 0;
}


SMART_ANT::~SMART_ANT() {
    for (size_t i = 0; i < generation.size(); i++) {
        delete generation[i];
    }
}

void SMART_ANT::makeFirstGeneration() {
    for (int i = 0; i < survivedAnts; i++) {
        generation.push_back(new ANT(genomeSize));
    }

}

void SMART_ANT::makeNextGeneration() {
    while(generation.size() < generationSize) {
        int i = rand() % (survivedAnts);
        int j = rand() % (survivedAnts);
        if(i == j) continue;
        if(rand() % 30 != 0) {
            makeLove(generation[i], generation[j]);
        } else {
            makeMutation(generation[i]);
            makeMutation(generation[j]);
        }
    }
    for (size_t i = 0; i < generation.size(); i++) {
        generation[i]->makeMoves(maxStepToAnt, sizeOfMap, appleNumber, torMap);
    }
    std::sort(generation.begin(), generation.end(), comparePriority);
    for (size_t i = survivedAnts; i < generation.size(); i++) {
        delete generation[i];
    }
    generation.resize(survivedAnts);
}

void SMART_ANT::makeLove(ANT* parent1, ANT* parent2) {
    ANT* child1 = new ANT(genomeSize);
    ANT* child2 = new ANT(genomeSize);
    if (rand() % 2 == 1) {
        child1->genome->startState = parent1->genome->startState;
        child2->genome->startState = parent2->genome->startState;
    } else {
        child1->genome->startState = parent2->genome->startState;
        child2->genome->startState = parent1->genome->startState;
    }
    for (int i = 0; i < genomeSize; i++) {
        STATE* st1;
        STATE* st2;
        STATE* pst1 = parent1->genome->states[i];
        STATE* pst2 = parent2->genome->states[i];
        switch (rand() % 4) {
        case 0:
            st1 = new STATE(pst1->outState0, pst2->outState1, pst1->actionToMove0, pst2->actionToMove1);
            st2 = new STATE(pst2->outState0, pst1->outState1, pst2->actionToMove0, pst1->actionToMove1);
            break;
        case 1:
            st1 = new STATE(pst2->outState0, pst1->outState1, pst2->actionToMove0, pst1->actionToMove1);
            st2 = new STATE(pst1->outState0, pst2->outState1, pst1->actionToMove0, pst2->actionToMove1);
            break;
        case 2:
            st1 = new STATE(pst1->outState0, pst1->outState1, pst1->actionToMove0, pst1->actionToMove1);
            st2 = new STATE(pst2->outState0, pst2->outState1, pst2->actionToMove0, pst2->actionToMove1);
            break;
        case 3:
            st1 = new STATE(pst2->outState0, pst2->outState1, pst2->actionToMove0, pst2->actionToMove1);
            st2 = new STATE(pst1->outState0, pst1->outState1, pst1->actionToMove0, pst1->actionToMove1);
            break;
        }
        delete child1->genome->states[i];
        delete child2->genome->states[i];
        child1->genome->states[i] = st1;
        child2->genome->states[i] = st2;
    }
    generation.push_back(child1);
    generation.push_back(child2);
}

void SMART_ANT::makeMutation(ANT* ant) {
    int i = rand() % genomeSize;
    STATE* st = ant->genome->states[i];

    switch (rand() % 6) {
        case 0:
            ant->genome->startState = rand() % genomeSize;
            break;
        case 1:
            st->actionToMove0 = (ACTION) (rand() % 4);
            break;
        case 2:
            st->actionToMove1 = (ACTION) (rand() % 4);
            break;
        case 3:
            st->outState0 = rand() % genomeSize;
            break;
        case 4:
            st->outState1 = rand() % genomeSize;
            break;
        case 5:
            int tempOut = st->outState0;
            ACTION tempAction = st->actionToMove0;
            st->outState0 = st->outState1;
            st->outState1 = tempOut;
            st->actionToMove0 = st->actionToMove1;
            st->actionToMove1 = tempAction;
            break;
    }
}

void SMART_ANT::makeLittleShake() {
    size_t gs = generation.size();
    for (size_t i = 1; i < gs; i++) {
        makeMutation(generation[i]);
    }
    for (size_t i = 0; i < generation.size(); i++) {
        generation[i]->makeMoves(maxStepToAnt, sizeOfMap, appleNumber, torMap);
    }
    std::sort(generation.begin(), generation.end(), comparePriority);
    for (size_t i = survivedAnts; i < generation.size(); i++) {
        delete generation[i];
    }
    generation.resize(survivedAnts);
    std::cout << std::endl << "Little Shake!" << std::endl;
}

void SMART_ANT::makeBigShake() {
    size_t gs = generation.size();
    for (size_t i = 0; i < generation.size(); i++) {
        if (rand() % 2 == 0) {
            makeMutation(generation[i]);
        } else {
            delete generation[i];
            generation[i] = new ANT(genomeSize);
        }
    }
    for (size_t i = 0; i < generation.size(); i++) {
        generation[i]->makeMoves(maxStepToAnt, sizeOfMap, appleNumber, torMap);
    }
    std::sort(generation.begin(), generation.end(), comparePriority);
    for (size_t i = survivedAnts; i < generation.size(); i++) {
        delete generation[i];
    }
    generation.resize(survivedAnts);
    std::cout << std::endl << "BIG SHAKE!" << std::endl;
}

ANT* SMART_ANT::makeMachine() {
    makeFirstGeneration();
    generationNumber = 1;
    int lastResult = 0;
    const int bigShake = 60;
    const int littleShake = 20;
    int generToLittleShake = littleShake;
    int generToBigShake = bigShake;
    while(generation[0]->returnAppleNumber() != appleNumber) {
        if (lastResult != generation[0]->returnAppleNumber()) {
            generToLittleShake = littleShake;
            generToBigShake = bigShake;
            lastResult = generation[0]->returnAppleNumber();
        }
        if(generToLittleShake == 0 && generToBigShake != 0) {
            generToLittleShake = littleShake;
            makeLittleShake();
        }
        if(generToBigShake == 0) {
            generToLittleShake = littleShake;
            generToBigShake = bigShake;
            makeBigShake();
        }
        makeNextGeneration();
        std::cout << "#" << generationNumber++ << ", apples was eat: " << generation[0]->returnAppleNumber() << " (" << appleNumber << ") " << generToLittleShake << " " << generToBigShake << std::endl;
        generToLittleShake--;
        generToBigShake--;
    }
    return generation[0];
}