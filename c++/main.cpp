#include "SMART_ANT.h"
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string fileName;
    std::cout << "File name: ";
    std::cin >> fileName;
    std::ifstream in(fileName.c_str());
    int generSize = 50000;
    int survivedSize = 1000; 
    int genomSize = 0;
    int maxStep = 0;
    int mapSize = 0;
    int apples = 0;
    in >> mapSize >> genomSize >> maxStep;
    int ** map = new int * [mapSize];
    for (int i = 0; i < mapSize; i++) {
        map[i] = new int[mapSize];
    }
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            char c;
            in >> c;
            map[i][j] = (c == '*') ? 1 : 0;
            apples += map[i][j];
        }
    }
    SMART_ANT gener(generSize, survivedSize, genomSize, maxStep, mapSize, apples, map);
    
    ANT * st = gener.makeMachine();
    std::cout << std::endl << fileName << std::endl;
    std::cout << std::endl << st->genome->startState << std::endl;
    char act[4];
    act[MOVE] = 'M';
    act[TURN_LEFT] = 'L';
    act[TURN_RIGHT] = 'R';
    act[NOTHING] = 'N';
    for (size_t i = 0; i < st->genome->states.size(); i++) {
        STATE* temp = st->genome->states[i];
        std::cout << temp->outState0 << " " << temp->outState1 << " " << act[temp->actionToMove0] << " " << act[temp->actionToMove1] << std::endl;
    }
    std::cin >> apples;
}