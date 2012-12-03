#include "ANT.h"


int sign(int x) {
    return (x >= 0) ? 1 : -1;
}

ANT::ANT(int size, GENOME* g) {
    genome = (g == NULL) ? new GENOME(size) : g;
    prior = -1;
    applesWasEat = 0;
    moveToEatAllApples = 0;
    rotation = 0;
    x = 0;
    y = 0;
}

int ANT::returnAppleNumber() {
    return applesWasEat;
}


ANT::~ANT() {
    delete genome;
}

float ANT::returnPriority() {
    return prior;
}

void ANT::makeMoves(int maxStep, int mapSize, int appleNumber, int ** mapSource) {
    int map[40][40];
    applesWasEat = 0;
    moveToEatAllApples = 0;
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            map[i][j] = mapSource[i][j];
        }
    }
    x = 0;
    y = 0;
    rotation = 0;
    STATE * st = genome->getStartState();
    int moves = 0;
    while(appleNumber && moves < maxStep) {

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
                --appleNumber;
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
    rotation = 0;
}

void ANT::changePrior(float p) {
    prior = p;
}