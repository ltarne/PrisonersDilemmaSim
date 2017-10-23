#pragma once
#include <map>
#include <vector>

using namespace std;

class Prisoner
{
public:
	Prisoner(map<string, vector<string>> strategy);
	~Prisoner();

	inline const map<string, vector<string>>& getStrategy() const{
		return strategy;
	}

	inline void setStrategy(map<string, vector<string>> strategy) {
		this->strategy = strategy;
	}

	inline void incrementALLOUTCOMES_W() {
		ALLOUTCOMES_W++;
	}

	inline void incrementALLOUTCOMES_X() {
		ALLOUTCOMES_X++;
	}

	inline void incrementALLOUTCOMES_Y() {
		ALLOUTCOMES_Y++;
	}

	inline void incrementALLOUTCOMES_Z() {
		ALLOUTCOMES_Z++;
	}

	inline void incrementITERATIONS() {
		ITERATIONS++;
	}

	inline void incrementMYSCORE(unsigned int years) {
		MYSCORE += years;
	}

	inline unsigned int getMYSCORE() {
		return MYSCORE;
	}

	unsigned int getVariable(const string word);


protected:

	map<string, vector<string>> strategy;

	unsigned int LASTOUTCOME;
	unsigned int ALLOUTCOMES_W;
	unsigned int ALLOUTCOMES_X;
	unsigned int ALLOUTCOMES_Y;
	unsigned int ALLOUTCOMES_Z;
	unsigned int ITERATIONS;
	unsigned int MYSCORE;
};

