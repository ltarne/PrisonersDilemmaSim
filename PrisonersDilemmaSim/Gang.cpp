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
	spy = leader;
	while (spy == leader) {
		spy = getRandomStrategy();
	}
}


bool Gang::findSpy() {
	vector<map<string, vector<string>>>::iterator possibleSpy = leader;

	while (possibleSpy == leader) {
		possibleSpy = getRandomStrategy();
	}
	vector<map<string, vector<string>>>::iterator revealedNonSpy = possibleSpy;
	while (revealedNonSpy == leader || revealedNonSpy == possibleSpy || revealedNonSpy == spy) {
		revealedNonSpy = getRandomStrategy();
	}
	vector<map<string, vector<string>>>::iterator finalChoice = possibleSpy;
	if (rand() % 2) {
		leaderSwap = true;
		while (finalChoice == leader || finalChoice == possibleSpy || finalChoice == possibleSpy) {
			finalChoice = getRandomStrategy();
		}
	}
	return finalChoice == spy;
}


