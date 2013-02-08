#include "ANT.h"


int sign(const int x) {
    return (x >= 0) ? 1 : -1;
}

ANT::ANT(const int size, GENOME* g) {
    genome = (g == 0) ? new GENOME(size) : g;
    prior = -1;
    applesWasEat = 0;
    moveToEatAllApples = 0;
}

int ANT::returnAppleNumber() const {
    return applesWasEat;
}


ANT::~ANT() {
    delete genome;
}

float ANT::returnPriority() const {
    return prior;
}

void ANT::makeMoves(const int maxStep, const int mapSize, const int appleNumber, char ** mapSource) {
    char map[40][40];
    int appNum = appleNumber;
    applesWasEat = 0;
    moveToEatAllApples = 0;
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            map[i][j] = mapSource[i][j];
        }
    }
    int x = 0;
    int y = 0;
    int rotation = 0;
    STATE * st = genome->getState(genome->getStartState());
    int moves = 0;
    while(appNum && moves < maxStep) {

        if(x >= mapSize || x < 0) {
            x = x - mapSize * sign(x);
        }
        if(y >= mapSize || y < 0) {
            y = y - mapSize * sign(y);
        }

        int nextX = x;
        int nextY = y;
        ACTION action;
        int outState;
        switch (rotation) {
        case 0:
            nextX += 1; 
            break;
        case 1:
            nextY += 1;
            break;
        case 2:
            nextX -= 1;
            break;
        case 3:
            nextY -= 1;
            break;
        }
        if(nextX >= mapSize || nextX < 0) {
            nextX = nextX - mapSize * sign(nextX);
        }
        if(nextY >= mapSize || nextY < 0) {
            nextY = nextY - mapSize * sign(nextY);
        }
        action = st->getAction(map[nextY][nextX]);
        outState = st->getOutState(map[nextY][nextX]);
        st = genome->getState(outState);

        switch (action) {
        case MOVE:
            x = nextX;
            y = nextY;
            if(map[nextY][nextX]) {
                --appNum;
                map[nextY][nextX] = 0;

                if(moves < maxStep) {
                    applesWasEat += 1;
                }
            }
            break;
        case TURN_LEFT:
            rotation -= 1;
            if (rotation < 0) {
                rotation = 3;
            }
            break;
        case TURN_RIGHT:
            rotation += 1;
            if (rotation > 3) {
                rotation = 0;
            }
            break;
        case NOTHING:
            break;
        }

        ++moves;
    }
    moveToEatAllApples = moves;
    prior = applesWasEat + (float)(maxStep - moveToEatAllApples) / ((float) maxStep);
}

void ANT::changePrior(const float p) {
    prior = p;
}

GENOME * ANT::getGenome() const {
    return genome;
}