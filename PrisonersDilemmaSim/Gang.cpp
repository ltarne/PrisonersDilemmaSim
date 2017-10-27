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
	//Iterate to next strategy
	nextStrategy++;
	if (nextStrategy == strategies.end()) {
		nextStrategy = strategies.begin();
		//return the original strategy
		return *(strategies.end() - 1);
	}
	//return the original strategy
	return *(nextStrategy - 1);
}

void Gang::chooseSpyAndLeader() {
	leader = getRandomStrategy();
	spy = leader;
	//Find random spy that isn't leader
	while (spy == leader) {
		spy = getRandomStrategy();
	}
}


bool Gang::findSpy() {
	vector<map<string, vector<string>>>::iterator possibleSpy = leader;

	//Leader makes first choice
	while (possibleSpy == leader) {
		possibleSpy = getRandomStrategy();
	}
	//Non spy is revealed to leader
	vector<map<string, vector<string>>>::iterator revealedNonSpy = possibleSpy;
	while (revealedNonSpy == leader || revealedNonSpy == possibleSpy || revealedNonSpy == spy) {
		revealedNonSpy = getRandomStrategy();
	}
	//Does the leader switch
	vector<map<string, vector<string>>>::iterator finalChoice = possibleSpy;
	if (rand() % 2) {
		leaderSwap = true;
		while (finalChoice == leader || finalChoice == possibleSpy || finalChoice == possibleSpy) {
			finalChoice = getRandomStrategy();
		}
	}
	return finalChoice == spy;
}


