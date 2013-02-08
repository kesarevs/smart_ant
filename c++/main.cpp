#include "SMART_ANT.h"
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>

int main(int argc, char *argv[]) {
    int genomSize = 0;
    int maxStep = 0;
    int mapSize = 0;
    int apples = 0;

    assert(argc != 1);
    std::ifstream in(argv[1]);

    in >> mapSize >> genomSize >> maxStep;

    char ** map = new char * [mapSize];
    for (int i = 0; i < mapSize; i++) {
        map[i] = new char[mapSize];
        for (int j = 0; j < mapSize; j++) {
            char c;
            in >> c;
            map[i][j] = (c == '*') ? 1 : 0;
            apples += map[i][j];
        }
    }
    SMART_ANT machine = SMART_ANT(genomSize, maxStep, mapSize, apples, map);
    ANT * ant = machine.makeMachine();
    std::cout << std::endl << argv[1] << std::endl;
    ant->printAnt();
    in.close();
}