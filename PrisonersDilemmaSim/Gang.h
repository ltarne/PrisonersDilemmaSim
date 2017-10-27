/* Collection of prisoners
* Author: Luke Burton 140274882
* Date: 27/10/2017
*/
#pragma once
#include "Prisoner.h"
class Gang :
	public Prisoner
{
public:
	Gang() {}

	Gang(vector<Prisoner*> prisoners, float spyPercentage = 0.0f);

	~Gang();

	/*Returns strategy map*/
	virtual const map<string, vector<string>>& getStrategy();

	/*Returns the next strategy in the strategy map*/
	inline vector<map<string, vector<string>>>::iterator getNextStrategy() {
		return nextStrategy;
	}

	/*Returns Spy iterator*/
	inline vector<map<string, vector<string>>>::iterator getSpy() {
		return spy;
	}

	/*Returns leader iterator*/
	inline vector<map<string, vector<string>>>::iterator getLeader() {
		return leader;
	}

	/*Returns if spys are being used*/
	inline bool isSpyInPlay() {
		return ((rand() % 100) < spyPercentage);
	}

	/*Appends strategy to strategies
	* strategy: Strategy to be absorbed
	*/
	inline void absorbStrategy(map<string, vector<string>> strategy) {
			strategies.push_back(strategy);
	}

	/*Set strategies from vector of prisoners
	* prisoners: Prisoners to take strategies from
	*/
	inline void setStrategies(vector<Prisoner*> prisoners) {
		for (int i = 0; i < prisoners.size(); ++i) {
			fileName.append(((i == 0) ? "" : " + ") + prisoners[i]->getFileName());
			absorbStrategy(prisoners[i]->getStrategy());
		}
	}

	/*Return strategies*/
	inline vector<map<string, vector<string>>>& getStrategies() {
		return strategies;
	}

	/*Return a random strategy*/
	inline vector<map<string, vector<string>>>::iterator getRandomStrategy() {
		return strategies.begin() + (rand() % strategies.size());
	}

	/*Set spy percentage*/
	inline void setSpyPercentage(float spyPercentage) {
		this->spyPercentage = spyPercentage;
	}

	/*Return spy percentage*/
	inline float getSpyPercentage() {
		return spyPercentage;
	}

	/*Choose both a spy and a leader*/
	void chooseSpyAndLeader();

	/*Get the leader to find the spy*/
	bool findSpy();

	/*Return if the leader swapped*/
	bool didLeaderSwap() {
		return leaderSwap;
	}

protected:
	vector<map<string, vector<string>>> strategies;
	vector<map<string, vector<string>>>::iterator nextStrategy;

	float spyPercentage;
	bool leaderSwap;

	vector<map<string, vector<string>>>::iterator spy;
	vector<map<string, vector<string>>>::iterator leader;

};

