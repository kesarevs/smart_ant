#include "STATE.h"


STATE::STATE(int out0, int out1, ACTION action0, ACTION action1) {
    outState0 = out0;
    outState1 = out1;
    actionToMove0 = action0;
    actionToMove1 = action1;
}

STATE::~STATE() {}

int STATE::getOutState(int id) {
    return (id == 0) ? outState0 : outState1;
}

ACTION STATE::getAction(int id) {
    return (id == 0) ? actionToMove0 : actionToMove1;
}