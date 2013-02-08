#include "STATE.h"
#include <assert.h>

STATE::STATE(const int out0, const int out1, const ACTION action0, const ACTION action1) {
    outStates[0] = out0;
    outStates[1] = out1;
    actionToMove[0] = action0;
    actionToMove[1] = action1;
}

STATE::~STATE() {}

int STATE::getOutState(const int id) const {
	assert(id == 0 || id == 1);
	return outStates[id];
}

ACTION STATE::getAction(const int id) const {
	assert(id == 0 || id == 1);
	return actionToMove[id];
}

void STATE::changeOutState(const int id, const int out) {
	assert(id == 0 || id == 1);
	assert(out >= 0);
	outStates[id] = out;
}

void STATE::changeAction(const int id, const ACTION act) {
	assert(id == 0 || id == 1);
	actionToMove[id] = act;
}