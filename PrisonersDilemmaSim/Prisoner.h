#pragma once
#include <map>
#include <vector>

using namespace std;

/* Outcomes of both prisoners combined */
enum overallOutcome {
	N,
	W,
	X,
	Y,
	Z,
	A,
	B,
	C
};

class Prisoner
{
public:
	Prisoner();
	Prisoner(map<string, vector<string>> strategy, string fileName);
	~Prisoner();

	virtual const map<string, vector<string>>& getStrategy() {
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

	inline void incrementALLOUTCOMES_A() {
		ALLOUTCOMES_A++;
	}

	inline void incrementALLOUTCOMES_B() {
		ALLOUTCOMES_B++;
	}

	inline void incrementALLOUTCOMES_C() {
		ALLOUTCOMES_C++;
	}

	inline void incrementITERATIONS() {
		ITERATIONS++;
	}

	inline void incrementMYSCORE(float years) {
		MYSCORE += years;
	}

	inline void setLASTOUTCOME(overallOutcome outcome) {
		LASTOUTCOME = outcome;
	}


	inline float getMYSCORE() {
		return MYSCORE;
	}

	inline string getFileName() {
		return fileName;
	}


	inline int getLASTOUTCOME() {
		return LASTOUTCOME;
	}

	unsigned int getVariable(const string word);

	void resetVariables();


protected:

	string fileName;

	map<string, vector<string>> strategy;

	unsigned int LASTOUTCOME;
	unsigned int ALLOUTCOMES_W;
	unsigned int ALLOUTCOMES_X;
	unsigned int ALLOUTCOMES_Y;
	unsigned int ALLOUTCOMES_Z;
	unsigned int ALLOUTCOMES_A;
	unsigned int ALLOUTCOMES_B;
	unsigned int ALLOUTCOMES_C;
	unsigned int ITERATIONS;
	float MYSCORE;
};

