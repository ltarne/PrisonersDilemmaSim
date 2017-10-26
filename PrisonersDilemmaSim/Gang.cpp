#include "Gang.h"



Gang::Gang(vector<Prisoner*> prisoners, float spyPercentage) {
	setStrategies(prisoners);
	nextStrategy = strategies.begin();
	this->spyPercentage = spyPercentage;
	leaderSwap = false;

}

Gang::~Gang() {
}

const map<string, vector<string>>& Gang::getStrategy() {

	nextStrategy++;
	if (nextStrategy == strategies.end()) {
		nextStrategy = strategies.begin();
		return *(strategies.end() - 1);
	}
	return *(nextStrategy - 1);
}

void Gang::chooseSpyAndLeader() {
	leader = getRandomStrategy();
	spy = getRandomStrategy();
}

bool Gang::findSpy() {
	/*vector<map<string, vector<string>>>::iterator possibleSpy;



	return possibleSpy == spy;*/
	return false;
}


