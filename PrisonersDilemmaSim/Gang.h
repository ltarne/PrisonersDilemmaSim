#pragma once
#include "Prisoner.h"
class Gang :
	public Prisoner
{
public:
	Gang() {
		
	}
	Gang(vector<Prisoner*> prisoners, float spyPercentage = 0.0f);

	~Gang();

	virtual const map<string, vector<string>>& getStrategy();

	inline vector<map<string, vector<string>>>::iterator getNextStrategy() {
		return nextStrategy;
	}

	inline vector<map<string, vector<string>>>::iterator getSpy() {
		return spy;
	}

	inline vector<map<string, vector<string>>>::iterator getLeader() {
		return leader;
	}

	inline bool isSpyInPlay() {
		return ((rand() % 100) < spyPercentage);
	}

	inline void absorbStrategy(map<string, vector<string>> strategy) {
			strategies.push_back(strategy);
	}

	inline void setStrategies(vector<Prisoner*> prisoners) {
		for (int i = 0; i < prisoners.size(); ++i) {
			fileName.append(((i == 0) ? "" : " + ") + prisoners[i]->getFileName());
			absorbStrategy(prisoners[i]->getStrategy());
		}
	}

	inline vector<map<string, vector<string>>>& getStrategies() {
		return strategies;
	}

	inline vector<map<string, vector<string>>>::iterator getRandomStrategy() {
		return strategies.begin() + (rand() % strategies.size());
	}

	void chooseSpyAndLeader();

	bool findSpy();

	bool didLeaderSwap() {
		return leaderSwap;
	}

protected:
	vector<map<string, vector<string>>> strategies;
	vector<map<string, vector<string>>>::iterator nextStrategy;

	float spyPercentage;
	bool leaderSwap;
	//bool isSpyInPlay = false;
	vector<map<string, vector<string>>>::iterator spy;
	vector<map<string, vector<string>>>::iterator leader;

};

