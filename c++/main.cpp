#include "SMART_ANT.h"
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string fileName;
    std::cout << "File name: ";
    std::cin >> fileName;
    std::ifstream in(fileName.c_str());
    int genomSize = 0;
    int maxStep = 0;
    int mapSize = 0;
    int apples = 0;
    in >> mapSize >> genomSize >> maxStep;
    char ** map = new char * [mapSize];
    for (int i = 0; i < mapSize; i++) {
        map[i] = new char[mapSize];
    }
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            char c;
            in >> c;
            map[i][j] = (c == '*') ? 1 : 0;
            apples += map[i][j];
        }
    }
    SMART_ANT gener(genomSize, maxStep, mapSize, apples, map);
    
    ANT * ant = gener.makeMachine();
    std::cout << std::endl << fileName << std::endl;
    std::cout << std::endl << "Start State: " << ant->getGenome()->getStartState() << std::endl;
    char act[4];
    act[MOVE] = 'M';
    act[TURN_LEFT] = 'L';
    act[TURN_RIGHT] = 'R';
    act[NOTHING] = 'N';
    for (size_t i = 0; i < ant->getGenome()->getGenomeSize(); i++) {
        STATE* temp = ant->getGenome()->getState(i);
        std::cout << i << ":  " << temp->getOutState(0) << " " << temp->getOutState(1) << " " << act[temp->getAction(0)] << " " << act[temp->getAction(1)] << std::endl;
    }
    std::cin >> apples;
}